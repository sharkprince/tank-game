#ifndef TANK_GAME_TANK_H
#define TANK_GAME_TANK_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../utils/animator.h"
#include "../core/game.h"
#include "bullet.h"

class Tank {
public:
    Tank(sf::Texture *, sf::Texture *);

    void GoUp(float);

    void GoRight(float);

    void GoDown(float);

    void GoLeft(float);

    void Shoot(float);

    void Update(Game *);

    sf::Sprite TankSprite;

private:
    float lastShootDurationSeconds;

    sf::Vector2f getGunPosition();

    sf::Texture *bulletTexture;

    Animator *animator;

    std::vector<Bullet *> bullets;
};


#endif //TANK_GAME_TANK_H
