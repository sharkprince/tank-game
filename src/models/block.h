#ifndef TANK_GAME_BLOCK_H
#define TANK_GAME_BLOCK_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../core/game.h"

class Block {
public:
    Block(sf::Texture *texture, sf::Vector2f position, bool isBreakable);

    void Update(Game *g);

    bool Hit(float rotation);

    sf::Sprite *Sprite;

    constexpr static float BLOCK_WIDTH_PIXELS = 24.f;
    constexpr static float BLOCK_HEIGHT_PIXELS = 24.f;
    constexpr static float FLOAT_BLOCK_HIT_DAMAGE = 6.f;

private:
    bool isBreakable;
    sf::Texture texture;
};


#endif //TANK_GAME_BLOCK_H
