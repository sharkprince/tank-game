#include "levels.h"

std::vector<BlockType> blockTypesLevel2 = {
        C, C, C, C, C, C, C, C, C, C, C, C, C, C, C,
        C, G, G, G, G, G, G, G, G, G, G, G, G, G, C,
        C, G, G, G, G, G, G, G, G, G, G, G, G, G, C,
        C, E, E, E, E, E, E, B, E, E, E, E, E, E, C,
        C, E, E, E, E, E, E, B, E, E, E, E, E, E, C,
        C, E, E, E, E, G, G, B, G, G, E, E, E, E, C,
        C, E, E, E, E, G, B, B, B, G, E, E, E, E, C,
        C, W, E, B, E, B, B, B, B, B, E, B, E, W, C,
        C, E, E, E, E, G, B, B, B, G, E, E, E, E, C,
        C, E, E, E, E, G, G, B, G, G, E, E, E, E, C,
        C, E, E, E, E, E, E, B, E, E, E, E, E, E, C,
        C, E, E, E, E, E, E, B, E, E, E, E, E, E, C,
        C, G, G, G, G, G, G, G, G, G, G, G, G, G, C,
        C, G, G, G, G, G, G, G, G, G, G, G, G, G, C,
        C, C, C, C, C, C, C, C, C, C, C, C, C, C, C,
};

Level *createNewLevelTwo(sf::Texture *waterTexture, sf::Texture *grassTexture, sf::Texture *cementTexture,
                         sf::Texture *brickTexture) {
    std::vector<std::vector<Block *>> blocks = Level::BuildBlocks(blockTypesLevel2, waterTexture, grassTexture, cementTexture,
                                                                  brickTexture);

    return new Level(blocks, 20);
}
