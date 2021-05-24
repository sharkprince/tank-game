#include "tank.h"
#include "../const/rotation.h"

const float MOVE_SPEED = 50.f;

const float SHOOT_INTERVAL_SECONDS = 1.f;
const float MOVE_ANIMATION_FRAME_DURATION_SECONDS = 0.05f;

const float GUN_LENGTH = 20;

Tank::Tank(sf::Texture *tankTexture, sf::Texture *bulletTexture) {
    TankSprite = sf::Sprite();
    TankSprite.setTexture(*tankTexture);
    TankSprite.setTextureRect(sf::IntRect(0, 0, 24, 31));
    TankSprite.setPosition(180, 120);
    TankSprite.setOrigin(sf::Vector2(12.f, 19.5f));

    this->bulletTexture = bulletTexture;

    lastShootDurationSeconds = SHOOT_INTERVAL_SECONDS;

    animator = new Animator(MOVE_ANIMATION_FRAME_DURATION_SECONDS, &TankSprite);
}

void Tank::GoUp(float elapsedSeconds) {
    this->animator->Update(elapsedSeconds);
    TankSprite.move(sf::Vector2f(0.f, -MOVE_SPEED * elapsedSeconds));
    TankSprite.setRotation(UP_ROTATION);
}

void Tank::GoRight(float elapsedSeconds) {
    this->animator->Update(elapsedSeconds);
    TankSprite.move(sf::Vector2f(MOVE_SPEED * elapsedSeconds, 0));
    TankSprite.setRotation(RIGHT_ROTATION);
}

void Tank::GoDown(float elapsedSeconds) {
    this->animator->Update(elapsedSeconds);
    TankSprite.move(sf::Vector2f(0, MOVE_SPEED * elapsedSeconds));
    TankSprite.setRotation(DOWN_ROTATION);
}

void Tank::GoLeft(float elapsedSeconds) {
    this->animator->Update(elapsedSeconds);
    TankSprite.move(sf::Vector2f(-MOVE_SPEED * elapsedSeconds, 0));
    TankSprite.setRotation(LEFT_ROTATION);
}

void Tank::Update(Game *g) {
    g->DrawSprite(&TankSprite);

    for (Bullet *b:bullets) {
        b->Update(g);
    }
}

sf::Vector2f Tank::getGunPosition() {
    float rotation = TankSprite.getRotation();
    sf::Vector2f tankPosition = TankSprite.getPosition();

    if (rotation == UP_ROTATION) {
        return sf::Vector2f(tankPosition.x, tankPosition.y - GUN_LENGTH);
    }
    if (rotation == RIGHT_ROTATION) {
        return sf::Vector2f(tankPosition.x + GUN_LENGTH, tankPosition.y);
    }
    if (rotation == DOWN_ROTATION) {
        return sf::Vector2f(tankPosition.x, tankPosition.y + GUN_LENGTH);
    }
    return sf::Vector2f(tankPosition.x - GUN_LENGTH, tankPosition.y);
}

void Tank::Shoot(float elapsedSeconds) {
    lastShootDurationSeconds += elapsedSeconds;
    if (lastShootDurationSeconds < SHOOT_INTERVAL_SECONDS) return;

    lastShootDurationSeconds = 0;

    sf::Vector2f gunPosition = getGunPosition();
    auto newBullet = new Bullet(bulletTexture, gunPosition.x, gunPosition.y, TankSprite.getRotation());
    bullets.push_back(newBullet);
}
