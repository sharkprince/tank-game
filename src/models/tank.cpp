#include "tank.h"
#include "../const/rotation.h"

const float MOVE_SPEED = 50.f;

const float SHOOT_INTERVAL_SECONDS = 1.f;
const float MOVE_ANIMATION_FRAME_DURATION_SECONDS = 0.1f;

const float GUN_LENGTH = 12;

Tank::Tank(sf::Vector2f position, sf::Texture *tankTexture, sf::Texture *bulletTexture) {
    TankSprite = sf::Sprite();
    TankSprite.setTexture(*tankTexture);
    TankSprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
    TankSprite.setPosition(position.x, position.y);
    TankSprite.setOrigin(sf::Vector2(12.f, 12.f));

    this->bulletTexture = bulletTexture;

    lastShootDurationSeconds = SHOOT_INTERVAL_SECONDS;

    animator = new Animator(MOVE_ANIMATION_FRAME_DURATION_SECONDS, &TankSprite);

    RandMove = -1;
}

sf::FloatRect Tank::GetGoUpBounds(float elapsedSeconds) {
    sf::FloatRect bounds = TankSprite.getGlobalBounds();
    bounds.top = bounds.top - (MOVE_SPEED * elapsedSeconds);
    return bounds;
}

void Tank::GoUp(float elapsedSeconds) {
    this->animator->Update(elapsedSeconds);
    TankSprite.move(sf::Vector2f(0.f, -MOVE_SPEED * elapsedSeconds));
    TankSprite.setRotation(UP_ROTATION);
}

sf::FloatRect Tank::GetGoRightBounds(float elapsedSeconds) {
    sf::FloatRect bounds = TankSprite.getGlobalBounds();
    bounds.left = bounds.left + (MOVE_SPEED * elapsedSeconds);
    return bounds;
}

void Tank::GoRight(float elapsedSeconds) {
    this->animator->Update(elapsedSeconds);
    TankSprite.move(sf::Vector2f(MOVE_SPEED * elapsedSeconds, 0));
    TankSprite.setRotation(RIGHT_ROTATION);
}

sf::FloatRect Tank::GetGoDownBounds(float elapsedSeconds) {
    sf::FloatRect bounds = TankSprite.getGlobalBounds();
    bounds.top = bounds.top + (MOVE_SPEED * elapsedSeconds);
    return bounds;
}

void Tank::GoDown(float elapsedSeconds) {
    this->animator->Update(elapsedSeconds);
    TankSprite.move(sf::Vector2f(0, MOVE_SPEED * elapsedSeconds));
    TankSprite.setRotation(DOWN_ROTATION);
}

sf::FloatRect Tank::GetGoLeftBounds(float elapsedSeconds) {
    sf::FloatRect bounds = TankSprite.getGlobalBounds();
    bounds.left = bounds.left - (MOVE_SPEED * elapsedSeconds);
    return bounds;
}

void Tank::GoLeft(float elapsedSeconds) {
    this->animator->Update(elapsedSeconds);
    TankSprite.move(sf::Vector2f(-MOVE_SPEED * elapsedSeconds, 0));
    TankSprite.setRotation(LEFT_ROTATION);
}

void Tank::Update(Game *g) {
    lastShootDurationSeconds += g->ElapsedSeconds;

    g->DrawSprite(&TankSprite);

    for (Bullet *b:Bullets) {
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

void Tank::Shoot() {
    if (lastShootDurationSeconds < SHOOT_INTERVAL_SECONDS) return;

    lastShootDurationSeconds = 0;

    sf::Vector2f gunPosition = getGunPosition();
    auto newBullet = new Bullet(bulletTexture, gunPosition.x, gunPosition.y, TankSprite.getRotation());
    Bullets.push_back(newBullet);
}
