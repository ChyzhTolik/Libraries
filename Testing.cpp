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
		sf::RenderWindow app_window( sf::VideoMode( {800, 600} ), "SFGUI Notebook Example", sf::Style::Titlebar | sf::Style::Close );

		// We have to do this because we don't use SFML to draw.
		app_window.resetGLStates();

		// Create an SFGUI. This is required before doing anything with SFGUI.
		sfg::SFGUI sfgui;

		// Create our main SFGUI window
		auto window = sfg::Window::Create();
		window->SetTitle( "Title" );

		// Create the notebook.
		auto notebook = sfg::Notebook::Create();

		// Create a couple of buttons to populate the notebook.
		auto button1 = sfg::Button::Create("Hello");
		auto button2 = sfg::Button::Create("World");

		// Add new pages to the notebook with respective tab labels
		// containing solely the buttons as their children.
		notebook->AppendPage( button1, sfg::Label::Create( "Page 1" ) );
		notebook->AppendPage( button2, sfg::Label::Create( "Page 2" ) );
		notebook->AppendPage( sfg::Label::Create(), sfg::Label::Create( "Page 3" ) );
		notebook->AppendPage( sfg::Label::Create(), sfg::Label::Create( "Page 4" ) );
		notebook->AppendPage( sfg::Label::Create(), sfg::Label::Create( "Page 5" ) );
		notebook->AppendPage( sfg::Label::Create(), sfg::Label::Create( "Page 6" ) );
		notebook->AppendPage( sfg::Label::Create(), sfg::Label::Create( "Page 7" ) );
		notebook->AppendPage( sfg::Label::Create(), sfg::Label::Create( "Page 8" ) );

		notebook->SetScrollable( true );
		notebook->SetRequisition( sf::Vector2f( 200.f, 0.f ) );

		// Add the notebook to the window.
		window->Add( notebook );

		sf::Clock clock;

		// Update an initial time to construct the GUI before drawing begins.
		// This makes sure that there are no frames in which no GUI is visible.
		window->Update( 0.f );

		// Start the game loop
		while ( app_window.isOpen() ) {
			// Process events
			sf::Event event;

			while ( app_window.pollEvent( event ) ) {
				// Handle events
				window->HandleEvent( event );

				// Close window : exit
				if ( event.type == sf::Event::Closed ) {
					return EXIT_SUCCESS;
				}
			}

			// Update the GUI every 5ms
			if( clock.getElapsedTime().asMicroseconds() >= 5000 ) {
				// Update() takes the elapsed time in seconds.
				window->Update( static_cast<float>( clock.getElapsedTime().asMicroseconds() ) / 1000000.f );

				clock.restart();
			}

			// Clear screen
			app_window.clear();

			// Draw the GUI
			sfgui.Display( app_window );

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