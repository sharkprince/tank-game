#ifndef TANK_GAME_TANK_H
#define TANK_GAME_TANK_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../utils/animator.h"
#include "../core/game.h"
#include "bullet.h"

class Tank {
public:
    Tank(sf::Vector2f, sf::Texture *, sf::Texture *, sf::Texture *);

    sf::FloatRect GetGoUpBounds(float);

    void GoUp(float);

    sf::FloatRect GetGoRightBounds(float);

    void GoRight(float);

    sf::FloatRect GetGoDownBounds(float);

    void GoDown(float);

    sf::FloatRect GetGoLeftBounds(float);

    void GoLeft(float);

    void Shoot();

    void Destroy();

    bool GetIsDestroyed();
    float GetExplosionDuration();

    void Update(Game *);

    sf::Sprite *TankSprite;

    std::vector<Bullet *> Bullets;

    int RandMove;
    float RandMoveLength;
    float ElapsedRandMove;

private:
    float lastShootDurationSeconds;

    float explosionDuration;

    bool isDestroyed;

    sf::Vector2f getGunPosition();

    sf::Texture *bulletTexture;

    sf::Sprite *explosionSprite;

    Animator *movingAnimator;

    Animator *explosionAnimator;

};


#endif //TANK_GAME_TANK_H
