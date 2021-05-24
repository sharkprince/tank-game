#ifndef TANK_GAME_BULLET_H
#define TANK_GAME_BULLET_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../core/game.h"

class Bullet {
public:
    Bullet(sf::Texture *, float, float, float);

    void Update(Game *);

private:
    sf::Sprite sprite;
};


#endif //TANK_GAME_BULLET_H
