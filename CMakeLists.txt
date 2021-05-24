cmake_minimum_required(VERSION 3.19)
project(tank_game)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(tank_game src/main.cpp src/core/game.cpp src/core/game_states/menu_state.cpp src/core/game_states/arcade_state.cpp src/models/tank.cpp src/models/tank.h src/utils/animator.cpp src/utils/animator.h src/models/bullet.cpp src/models/bullet.h src/const/rotation.h)

target_link_libraries(tank_game sfml-graphics sfml-audio)