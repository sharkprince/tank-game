#ifndef TANK_GAME_ANIMATOR_H
#define TANK_GAME_ANIMATOR_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Animator {
public:
    Animator(float, sf::Sprite *);

    void Update(float);

private:
    float frameDuration;
    float elapsedFromLastAnimation;
    int textureWidth;
    sf::Sprite *sprite;
};


#endif //TANK_GAME_ANIMATOR_H
