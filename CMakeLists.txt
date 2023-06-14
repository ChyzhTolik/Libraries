cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

project(Libraries)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(libraries/SFML)
add_subdirectory(libraries/SFGUI)
add_subdirectory(libraries/box2d)

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

            ${CMAKE_SOURCE_DIR}/built_libraries/
)

message (555-${CMAKE_SOURCE_DIR})