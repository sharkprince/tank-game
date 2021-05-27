#ifndef TANK_GAME_TANK_H
#define TANK_GAME_TANK_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../utils/animator.h"
#include "../core/game.h"
#include "bullet.h"

class Tank {
public:
    Tank(sf::Vector2f, sf::Texture *, sf::Texture *);

    sf::FloatRect GetGoUpBounds(float);

    void GoUp(float);

    sf::FloatRect GetGoRightBounds(float);

    void GoRight(float);

    sf::FloatRect GetGoDownBounds(float);

    void GoDown(float);

    sf::FloatRect GetGoLeftBounds(float);

    void GoLeft(float);

    void Shoot();

    void Update(Game *);

    sf::Sprite TankSprite;

    std::vector<Bullet *> Bullets;

private:
    float lastShootDurationSeconds;

    sf::Vector2f getGunPosition();

    sf::Texture *bulletTexture;

    Animator *animator;

};


#endif //TANK_GAME_TANK_H
