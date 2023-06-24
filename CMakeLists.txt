cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)

project(Libraries)

add_executable(${PROJECT_NAME} main.cpp "Testing.cpp")

add_subdirectory(libraries/SFML)
add_subdirectory(libraries/SFGUI)
add_subdirectory(libraries/box2d)


target_include_directories(${PROJECT_NAME} PRIVATE 
    libraries/box2d/include
    libraries/SFGUI/include
    libraries/SFML/include
)

if(UNIX)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/built_libraries/UNIX/libsfml-audio-d.so.3.0.0
    ${CMAKE_SOURCE_DIR}/built_libraries/UNIX/libsfml-window-d.so.3.0.0
    ${CMAKE_SOURCE_DIR}/built_libraries/UNIX/libsfml-system-d.so.3.0.0
    ${CMAKE_SOURCE_DIR}/built_libraries/UNIX/libsfml-graphics-d.so.3.0.0

    ${CMAKE_SOURCE_DIR}/built_libraries/UNIX/libSFGUI-d.so

    ${CMAKE_SOURCE_DIR}/built_libraries/UNIX/libbox2d.so.2.4.1
)
endif(UNIX)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/built_libraries/Windows/sfml-graphics-d.lib
        ${CMAKE_SOURCE_DIR}/built_libraries/Windows/sfml-window-d.lib
        ${CMAKE_SOURCE_DIR}/built_libraries/Windows/sfml-system-d.lib
        ${CMAKE_SOURCE_DIR}/built_libraries/Windows/sfml-audio-d.lib

        ${CMAKE_SOURCE_DIR}/built_libraries/Windows/SFGUI-d.lib

        ${CMAKE_SOURCE_DIR}/built_libraries/Windows/box2d.lib
    )
endif(WIN32)

if(UNIX)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-audio-d.so.3.0.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-window-d.so.3.0.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-system-d.so.3.0.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-graphics-d.so.3.0.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-network-d.so.3.0.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-audio-d.so.3.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-window-d.so.3.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-system-d.so.3.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-graphics-d.so.3.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-audio-d.so
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-window-d.so
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-system-d.so
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-graphics-d.so
            ${CMAKE_BINARY_DIR}/libraries/SFGUI/lib/libSFGUI-d.so
            ${CMAKE_BINARY_DIR}/libraries/box2d/bin/libbox2d.so.2.4.1
            ${CMAKE_BINARY_DIR}/libraries/box2d/bin/libbox2d.so.2
            ${CMAKE_BINARY_DIR}/libraries/box2d/bin/libbox2d.so

            ${CMAKE_SOURCE_DIR}/built_libraries/UNIX
)

endif(UNIX)

if(WIN32)
    add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/libraries/SFML/extlibs/bin/x64/openal32.dll

            ${CMAKE_BINARY_DIR}/libraries/SFML/bin/sfml-audio-d-3.dll
            ${CMAKE_BINARY_DIR}/libraries/SFML/bin/sfml-graphics-d-3.dll
            ${CMAKE_BINARY_DIR}/libraries/SFML/bin/sfml-network-d-3.dll
            ${CMAKE_BINARY_DIR}/libraries/SFML/bin/sfml-system-d-3.dll
            ${CMAKE_BINARY_DIR}/libraries/SFML/bin/sfml-window-d-3.dll

            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/sfml-audio-d.lib
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/sfml-graphics-d.lib
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/sfml-network-d.lib
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/sfml-system-d.lib
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/sfml-window-d.lib

            ${CMAKE_BINARY_DIR}/libraries/box2d/bin/box2d.dll
            ${CMAKE_BINARY_DIR}/libraries/box2d/bin/box2d.lib

            ${CMAKE_BINARY_DIR}/libraries/SFGUI/lib/SFGUI-d.dll
            ${CMAKE_BINARY_DIR}/libraries/SFGUI/lib/SFGUI-d.lib

            ${CMAKE_SOURCE_DIR}/built_libraries/Windows
    )

    add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/libraries/SFML/bin/sfml-audio-d-3.dll
            ${CMAKE_BINARY_DIR}/libraries/SFML/bin/sfml-graphics-d-3.dll
            ${CMAKE_BINARY_DIR}/libraries/SFML/bin/sfml-network-d-3.dll
            ${CMAKE_BINARY_DIR}/libraries/SFML/bin/sfml-system-d-3.dll
            ${CMAKE_BINARY_DIR}/libraries/SFML/bin/sfml-window-d-3.dll

            ${CMAKE_BINARY_DIR}/libraries/box2d/bin/box2d.dll

            ${CMAKE_BINARY_DIR}/libraries/SFGUI/lib/SFGUI-d.dll

            ${CMAKE_BINARY_DIR}/
    )
endif(WIN32)

file(COPY ${CMAKE_SOURCE_DIR}/libraries/SFML/include/ DESTINATION ${CMAKE_SOURCE_DIR}/built_libraries/include)
file(COPY ${CMAKE_SOURCE_DIR}/libraries/SFGUI/include/ DESTINATION ${CMAKE_SOURCE_DIR}/built_libraries/include)
file(COPY ${CMAKE_SOURCE_DIR}/libraries/box2d/include/ DESTINATION ${CMAKE_SOURCE_DIR}/built_libraries/include)