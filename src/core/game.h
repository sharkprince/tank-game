#ifndef TANK_GAME_GAME_H
#define TANK_GAME_GAME_H

#include <SFML/Graphics.hpp>

class GameState;

class Game {
public:
    Game();

    void Start();

    void DrawSprite(sf::Sprite *);

    void RunArcade(int playersCount);

    void RunMenu();

    void Close();

    float ElapsedSeconds;

    sf::Texture *MenuTexture;

    sf::Texture *TankTexture;

    sf::Texture *TankTwoTexture;

    sf::Texture *BulletTexture;

    sf::Texture *BricksTexture;

    sf::Texture *CementTexture;

    sf::Texture *EnemyTankTexture;

    sf::Texture *ExplosionTexture;

private:
    sf::RenderWindow window;
    sf::Clock clock;

    GameState *state;
    GameState *newState;

    bool areArcadeTexturesLoaded;
    bool areMenuTexturesLoaded;
};

class GameState {
public:
    virtual void Update() = 0;

    virtual void UpdateOnEvent(sf::Event) = 0;

protected:
    Game *game;
};


#endif //TANK_GAME_GAME_H
