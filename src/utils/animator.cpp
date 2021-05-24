#include "animator.h"

Animator::Animator(float frameDuration, sf::Sprite *s) {
    this->frameDuration = frameDuration;
    elapsedFromLastAnimation = 0;
    textureWidth = s->getTexture()->getSize().x;
    sprite = s;
}

void Animator::Update(float elapsedSeconds) {
    elapsedFromLastAnimation += elapsedSeconds;
    if (elapsedFromLastAnimation < frameDuration) return;

    elapsedFromLastAnimation = 0;

    sf::IntRect spriteRect = sprite->getTextureRect();
    int newXRaw = spriteRect.left + spriteRect.width;
    int newX = newXRaw >= textureWidth ? 0 : newXRaw;
    sprite->setTextureRect(sf::IntRect(newX, 0, spriteRect.width, spriteRect.height));
}
