#include "bullet.h"
#include "../const/rotation.h"

const float MOVE_SPEED = 70.f;

Bullet::Bullet(sf::Texture *bulletTexture, float x, float y, float rotation) {
    Sprite = sf::Sprite();
    Sprite.setTexture(*bulletTexture);
    Sprite.setPosition(x, y);
    Sprite.setTextureRect(sf::IntRect(0, 0, 2, 3));
    Sprite.setOrigin(sf::Vector2(1.f, 1.5f));
    Sprite.setRotation(rotation);
}

void Bullet::Update(Game *g) {
    float rotation = Sprite.getRotation();
    if (rotation == UP_ROTATION) {
        Sprite.move(sf::Vector2f(0, -MOVE_SPEED * g->ElapsedSeconds));
    }
    if (rotation == RIGHT_ROTATION) {
        Sprite.move(sf::Vector2f(MOVE_SPEED * g->ElapsedSeconds, 0));
    }
    if (rotation == DOWN_ROTATION) {
        Sprite.move(sf::Vector2f(0, MOVE_SPEED * g->ElapsedSeconds));
    }
    if (rotation == LEFT_ROTATION) {
        Sprite.move(sf::Vector2f(-MOVE_SPEED * g->ElapsedSeconds, 0));
    }
    g->DrawSprite(&Sprite);
}
