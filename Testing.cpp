#include "Testing.hpp"

#include <SFML/Graphics.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <box2d/box2d.h>

#include "converter.hpp"

namespace Testing
{
	int test_sfml()
	{
        sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }

        return 0;
	}

    int text_sfgui()
    {
		// Create the main SFML window
		sf::RenderWindow app_window(sf::VideoMode({ 800, 600 }), "SFGUI Buttons Example", sf::Style::Titlebar | sf::Style::Close);

		// We have to do this because we don't use SFML to draw.
		app_window.resetGLStates();

		// Create an SFGUI. This is required before doing anything with SFGUI.
		sfg::SFGUI sfgui;

		// Create our main SFGUI window
		auto window = sfg::Window::Create();
		window->SetTitle("Title");

		// Create a Box to contain all our fun buttons ;)
		auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);

		// Create the Button itself.
		auto button = sfg::Button::Create("Click me");

		// Add the Button to the Box
		box->Pack(button);

		// So that our Button has a meaningful purpose
		// (besides just looking awesome :P) we need to tell it to connect
		// to a callback of our choosing to notify us when it is clicked.
		button->GetSignal(sfg::Widget::OnLeftClick).Connect([&button] {
			// When the Button is clicked it's label should change.
			button->SetLabel("I was clicked");
			});

		// If attempting to connect to a class method you need to provide
		// a pointer to it as the second parameter after the function address.
		// Refer to the Signals example for more information.

		// Create the ToggleButton itself.
		auto toggle_button = sfg::ToggleButton::Create("Toggle me");

		// Connect the OnToggle signal to our handler.
		toggle_button->GetSignal(sfg::ToggleButton::OnToggle).Connect([&toggle_button, &window] {
			// When the ToggleButton is active hide the window's titlebar.
			if (toggle_button->IsActive()) {
				window->SetStyle(window->GetStyle() ^ sfg::Window::TITLEBAR);
			}
			else {
				window->SetStyle(window->GetStyle() | sfg::Window::TITLEBAR);
			}
			});

		// Add the ToggleButton to the Box
		box->Pack(toggle_button);

		// Create the CheckButton itself.
		auto check_button = sfg::CheckButton::Create("Check me");

		// Since a CheckButton is also a ToggleButton we can use
		// ToggleButton signals to handle events for CheckButtons.
		check_button->GetSignal(sfg::ToggleButton::OnToggle).Connect([&check_button, &window] {
			// When the CheckButton is active hide the window's background.
			if (check_button->IsActive()) {
				window->SetStyle(window->GetStyle() ^ sfg::Window::BACKGROUND);
			}
			else {
				window->SetStyle(window->GetStyle() | sfg::Window::BACKGROUND);
			}
			});

		// Add the CheckButton to the Box
		box->Pack(check_button);

		// Just to keep things tidy ;)
		box->Pack(sfg::Separator::Create());

		// Create our RadioButtons.
		// RadioButtons each have a group they belong to. If not specified,
		// a new group is created by default for each RadioButton. You can
		// then use RadioButton::SetGroup() to set the group of a RadioButton
		// after you create them. If you already know which buttons will belong
		// to the same group you can just pass the group of the first button
		// to the following buttons when you construct them as we have done here.
		auto radio_button1 = sfg::RadioButton::Create("Either this");
		auto radio_button2 = sfg::RadioButton::Create("Or this", radio_button1->GetGroup());
		auto radio_button3 = sfg::RadioButton::Create("Or maybe even this", radio_button1->GetGroup());

		// Set the third RadioButton to be the active one.
		// By default none of the RadioButtons are active at start.
		radio_button3->SetActive(true);

		auto button_select = [&radio_button1, &radio_button2, &radio_button3, &window] {
			// Depending on which RadioButton is active
			// we set the window title accordingly.
			if (radio_button1->IsActive()) {
				window->SetTitle("First button selected");
			}
			else if (radio_button2->IsActive()) {
				window->SetTitle("Second button selected");
			}
			else if (radio_button3->IsActive()) {
				window->SetTitle("Third button selected");
			}
		};

		// Here we use the same handler for all three RadioButtons.
		// RadioButtons are CheckButtons and therefore also ToggleButtons,
		// hence we can use ToggleButton signals with RadioButtons as well.
		radio_button1->GetSignal(sfg::ToggleButton::OnToggle).Connect(button_select);
		radio_button2->GetSignal(sfg::ToggleButton::OnToggle).Connect(button_select);
		radio_button3->GetSignal(sfg::ToggleButton::OnToggle).Connect(button_select);

		// Add the RadioButtons to the Box
		box->Pack(radio_button1);
		box->Pack(radio_button2);
		box->Pack(radio_button3);

		// Finally add the Box to the window.
		window->Add(box);

		// Start the game loop
		while (app_window.isOpen()) {
			// Process events
			sf::Event event;

			while (app_window.pollEvent(event)) {
				// Handle events
				window->HandleEvent(event);

				// Close window : exit
				if (event.type == sf::Event::Closed) {
					return EXIT_SUCCESS;
				}
			}

			// Update the GUI, note that you shouldn't normally
			// pass 0 seconds to the update method.
			window->Update(0.f);

			// Clear screen
			app_window.clear();

			// Draw the GUI
			sfgui.Display(app_window);

			// Update the window
			app_window.display();
		}

		return EXIT_SUCCESS;
    }

	b2Body* create_box(b2World& world,int pos_x,int pos_y, int size_x,int size_y,b2BodyType type = b2_dynamicBody)
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set(converter::pixel_to_meters<double>(pos_x),converter::pixel_to_meters<double>(pos_y));
        bodyDef.type = type;


        b2PolygonShape b2shape;
        b2shape.SetAsBox(converter::pixel_to_meters<double>(size_x/2.0),converter::pixel_to_meters<double>(size_y/2.0));

        sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(size_x,size_y));
        shape->setOrigin({size_x/2.0f,size_y/2.0f});
        shape->setPosition(sf::Vector2f(pos_x,pos_y));

        if(type == b2_dynamicBody)
            shape->setFillColor(sf::Color::Blue);
        else
            shape->setFillColor(sf::Color::White);

        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0.4;
        fixtureDef.restitution= 0.5;
        fixtureDef.shape = &b2shape;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(shape);

        b2Body* res = world.CreateBody(&bodyDef);
        res->CreateFixture(&fixtureDef);


        // res->SetUserData(shape);

        return res;
    }

	void display_world(b2World& world,sf::RenderWindow& render)
    {
        world.Step(1.0/60,int32(8),int32(3));

        render.clear();

        for (b2Body* body=world.GetBodyList(); body!=nullptr; body=body->GetNext())
        {   
            sf::Shape* shape = reinterpret_cast<sf::Shape*>(body->GetUserData().pointer);
            shape->setPosition({converter::meters_to_pixels(body->GetPosition().x),converter::meters_to_pixels(body->GetPosition().y)});

            // sf::Angle angle(degrees(converter::rad_to_deg<float>(body->GetAngle())));

            shape->setRotation(sf::degrees(converter::rad_to_deg<float>(body->GetAngle())));
            render.draw(*shape);
        }

        render.display();
    }

	int test_box2d()
	{   

		sf::RenderWindow window(sf::VideoMode({800, 600}, 32), "04_Basic");
		window.setFramerateLimit(60);

		b2Vec2 gravity(0.f, 9.8f);
		b2World world(gravity);

		std::list<b2Body*> bodies;

		bodies.emplace_back(create_box(world,400,590,800,20,b2_staticBody));


		while(window.isOpen())
		{
			sf::Event event;
			while(window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)//Close window
					window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int x = sf::Mouse::getPosition(window).x;
				int y = sf::Mouse::getPosition(window).y;
				bodies.emplace_back(create_box(world,x,y,32,32));
			}
			display_world(world,window);
		}

		for(b2Body* body : bodies)
		{
			delete reinterpret_cast<sf::RectangleShape*>(body->GetUserData().pointer);
			world.DestroyBody(body);
		}

		return 0;
	}
}