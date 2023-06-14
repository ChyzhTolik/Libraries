cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

project(Libraries)

add_subdirectory(libraries/SFML)
add_subdirectory(libraries/SFGUI)
add_subdirectory(libraries/box2d)