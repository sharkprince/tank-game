#ifndef TANK_GAME_GAME_H
#define TANK_GAME_GAME_H

#include <SFML/Graphics.hpp>

class GameState;

class Game {
public:
    Game();

    void Start();

    void DrawSprite(sf::Sprite *);

    void RunArcade();

    void RunMenu();

    void Close();

    float ElapsedSeconds;

    sf::Texture BulletTexture;

private:
    sf::RenderWindow window;
    sf::Clock clock;

    GameState *state;
    GameState *newState;

    bool areArcadeTexturesLoaded;
    sf::Texture tankTexture;
};

class GameState {
public:
    virtual void Update() = 0;

    virtual void UpdateOnEvent(sf::Event) = 0;

protected:
    Game *game;
};


#endif //TANK_GAME_GAME_H
