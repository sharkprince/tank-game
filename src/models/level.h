#ifndef TANK_GAME_LEVEL_H
#define TANK_GAME_LEVEL_H


#include <vector>
#include "block.h"

enum BlockType {
    B,
    E,
    C,
    W,
    G,
};

class Level {
public:
    Level(std::vector<std::vector<Block *>>);

    void Update(Game *g);

    Block* AreBoundsIntersectBlock(sf::FloatRect bounds, sf::Vector2i blockPosition);
    std::vector<Block*> AreBoundsIntersectBlocks(sf::FloatRect bounds);

    static sf::Vector2f BlocksToDisplayPosition(sf::Vector2i position);

    static sf::Vector2i DisplayToBlocksPosition(sf::Vector2f position);

    static std::vector<std::vector<Block *>> BuildBlocks(std::vector<BlockType> types, sf::Texture *cementTexture, sf::Texture *brickTexture);

private:
    std::vector<std::vector<Block *>> blocks;

    constexpr static float POSITION_X = 140.f;
    constexpr static float POSITION_Y = 0.f;
    constexpr static int LEVEL_WIDTH_IN_BLOCKS = 15;
    constexpr static int LEVEL_HEIGHT_IN_BLOCKS = 15;

};


#endif //TANK_GAME_LEVEL_H
