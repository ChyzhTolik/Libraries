cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

project(Libraries)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(libraries/SFML)
add_subdirectory(libraries/SFGUI)
add_subdirectory(libraries/box2d)

if(UNIX)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-audio-d.so.3.0.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-window-d.so.3.0.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-system-d.so.3.0.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-graphics-d.so.3.0.0
            ${CMAKE_BINARY_DIR}/libraries/SFML/lib/libsfml-network-d.so.3.0.0
            ${CMAKE_BINARY_DIR}/libraries/SFGUI/lib/libSFGUI-d.so
            ${CMAKE_BINARY_DIR}/libraries/box2d/bin/libbox2d.so.2.4.1

            ${CMAKE_SOURCE_DIR}/built_libraries/UNIX
)
endif(UNIX)

if(WIN32)
    add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
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
endif(WIN32)