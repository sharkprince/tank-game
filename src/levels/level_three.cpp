#include "levels.h"

std::vector<BlockType> blockTypesLevel3 = {
        C, C, C, C, C, C, C, C, C, C, C, C, C, C, C,
        C, E, E, E, E, E, E, E, E, E, E, E, E, E, C,
        C, E, G, G, G, G, G, G, G, G, G, G, G, E, C,
        C, E, G, G, G, G, G, W, G, G, G, G, G, E, C,
        C, E, G, G, E, E, E, W, E, E, E, G, G, E, C,
        C, E, G, G, E, G, G, W, G, G, E, G, G, E, C,
        C, E, G, G, E, G, W, W, W, G, E, G, G, E, C,
        C, W, G, W, E, W, W, W, W, W, E, W, G, W, C,
        C, E, G, G, E, G, W, W, W, G, E, G, G, E, C,
        C, E, G, G, E, G, G, W, G, G, E, G, G, E, C,
        C, E, G, G, E, E, E, W, E, E, E, G, G, E, C,
        C, E, G, G, G, G, G, W, G, G, G, G, G, E, C,
        C, E, G, G, G, G, G, G, G, G, G, G, G, E, C,
        C, E, E, E, E, E, E, E, E, E, E, E, E, E, C,
        C, C, C, C, C, C, C, C, C, C, C, C, C, C, C,
};

Level *createNewLevelThree(sf::Texture *waterTexture, sf::Texture *grassTexture, sf::Texture *cementTexture,
                         sf::Texture *brickTexture) {
    std::vector<std::vector<Block *>> blocks = Level::BuildBlocks(blockTypesLevel3, waterTexture, grassTexture, cementTexture,
                                                                  brickTexture);

    return new Level(blocks, 25);
}
