#include "bullet.h"
#include "../const/rotation.h"

const float MOVE_SPEED = 70.f;

Bullet::Bullet(sf::Texture *bulletTexture, float x, float y, float rotation) {
    sprite = sf::Sprite();
    sprite.setTexture(*bulletTexture);
    sprite.setPosition(x, y);
    sprite.setTextureRect(sf::IntRect(0, 0, 2, 3));
    sprite.setOrigin(sf::Vector2(1.f, 1.5f));
    sprite.setRotation(rotation);
}

void Bullet::Update(Game *g) {
    float rotation = sprite.getRotation();
    if (rotation == UP_ROTATION) {
        sprite.move(sf::Vector2f(0, -MOVE_SPEED * g->ElapsedSeconds));
    }
    if (rotation == RIGHT_ROTATION) {
        sprite.move(sf::Vector2f(MOVE_SPEED * g->ElapsedSeconds, 0));
    }
    if (rotation == DOWN_ROTATION) {
        sprite.move(sf::Vector2f(0, MOVE_SPEED * g->ElapsedSeconds));
    }
    if (rotation == LEFT_ROTATION) {
        sprite.move(sf::Vector2f(-MOVE_SPEED * g->ElapsedSeconds, 0));
    }
    g->DrawSprite(&sprite);
}
