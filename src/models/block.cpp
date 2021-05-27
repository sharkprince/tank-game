#include "block.h"
#include "../const/rotation.h"

Block::Block(sf::Texture *texture, sf::Vector2f position, bool isBreakable) {
    Sprite = new sf::Sprite();
    Sprite->setTexture(*texture);
    Sprite->setPosition(position.x, position.y);
    Sprite->setTextureRect(sf::IntRect(0, 0, BLOCK_WIDTH_PIXELS, BLOCK_HEIGHT_PIXELS));
    Sprite->setRotation(0);

    this->isBreakable = isBreakable;
}

void Block::Update(Game *g) {
    g->DrawSprite(this->Sprite);
}

bool Block::Hit(float rotation) {
    if (!isBreakable) return false;

    sf::IntRect textureRect = Sprite->getTextureRect();
    sf::Vector2f origin = Sprite->getOrigin();

    if (rotation == LEFT_ROTATION) {
        Sprite->setOrigin(origin.x - FLOAT_BLOCK_HIT_DAMAGE, origin.y);
        Sprite->setTextureRect(
                sf::IntRect(
                        textureRect.left + FLOAT_BLOCK_HIT_DAMAGE,
                        textureRect.top,
                        textureRect.width - FLOAT_BLOCK_HIT_DAMAGE,
                        textureRect.height
                ));
    }

    if (rotation == UP_ROTATION) {
        Sprite->setOrigin(origin.x, origin.y - FLOAT_BLOCK_HIT_DAMAGE);
        Sprite->setTextureRect(
                sf::IntRect(
                        textureRect.left,
                        textureRect.top + FLOAT_BLOCK_HIT_DAMAGE,
                        textureRect.width,
                        textureRect.height - FLOAT_BLOCK_HIT_DAMAGE
                ));
    }

    if (rotation == RIGHT_ROTATION) {
        Sprite->setTextureRect(
                sf::IntRect(
                        textureRect.left,
                        textureRect.top,
                        textureRect.width - FLOAT_BLOCK_HIT_DAMAGE,
                        textureRect.height
                ));
    }

    if (rotation == DOWN_ROTATION) {
        Sprite->setTextureRect(
                sf::IntRect(
                        textureRect.left,
                        textureRect.top,
                        textureRect.width,
                        textureRect.height - FLOAT_BLOCK_HIT_DAMAGE
                ));
    }

    return false;
}
