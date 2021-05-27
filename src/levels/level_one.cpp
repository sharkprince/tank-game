#include "level_one.h"

std::vector<BlockType> blockTypes = {
        C, C, C, C, C, C, C, C, C, C, C, C, C, C, C,
        C, E, E, E, E, E, E, E, E, E, E, E, E, E, C,
        C, E, B, E, B, E, B, E, B, E, B, E, B, E, C,
        C, E, B, E, B, E, B, E, B, E, B, E, B, E, C,
        C, E, B, E, B, E, B, B, B, E, B, E, B, E, C,
        C, E, B, E, B, E, B, E, B, E, B, E, B, E, C,
        C, E, E, E, E, E, E, E, E, E, E, E, E, E, C,
        C, C, E, B, B, B, B, E, B, B, B, B, E, C, C,
        C, E, E, E, E, E, E, E, E, E, E, E, E, E, C,
        C, E, B, E, B, E, B, E, B, E, B, E, B, E, C,
        C, E, B, E, B, E, B, B, B, E, B, E, B, E, C,
        C, E, B, E, B, E, B, E, B, E, B, E, B, E, C,
        C, E, B, E, B, E, B, E, B, E, B, E, B, E, C,
        C, E, E, E, E, E, E, E, E, E, E, E, E, E, C,
        C, C, C, C, C, C, C, C, C, C, C, C, C, C, C,
};

Level *createNewLevelOne(sf::Texture *cementTexture, sf::Texture *brickTexture) {
    std::vector<std::vector<Block *>> blocks = Level::BuildBlocks(blockTypes, cementTexture, brickTexture);

    return new Level(blocks, 15);
}
