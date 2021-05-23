#ifndef TANK_GAME_CORE_H
#define TANK_GAME_CORE_H

#include <SFML/Graphics.hpp>

class GameState;

class Game {
public:
    Game();

    void start();

    void runArcade();

    sf::Clock clock;

private:
    void checkForClose();

    sf::RenderWindow window;
    GameState *state;
    GameState *newState;
};

class GameState {
public:
    virtual void update(Game *) = 0;
};


#endif //TANK_GAME_CORE_H
