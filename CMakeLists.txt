cmake_minimum_required(VERSION 3.19)
project(tank_game)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(tank_game main.cpp)

target_link_libraries(tank_game sfml-graphics sfml-audio)