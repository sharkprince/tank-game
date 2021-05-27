#include "level.h"

#include <utility>
#include <cmath>

sf::Vector2f Level::BlocksToDisplayPosition(sf::Vector2i position) {
    return sf::Vector2f(
            POSITION_X + (position.x * Block::BLOCK_WIDTH_PIXELS),
            POSITION_Y + (position.y * Block::BLOCK_HEIGHT_PIXELS)
    );
}

sf::Vector2i Level::DisplayToBlocksPosition(sf::Vector2f position) {
    int x = std::lrint((position.x - POSITION_X) / Block::BLOCK_WIDTH_PIXELS);
    int y = std::lrint((position.y - POSITION_Y) / Block::BLOCK_HEIGHT_PIXELS);
    return sf::Vector2i(x, y);
}

Level::Level(std::vector<std::vector<Block *>> blocks) {
    this->blocks = std::move(blocks);
}

void Level::Update(Game *g) {
    for (std::vector<Block *> b:blocks) {
        for (Block *bb: b) {
            if (bb != nullptr) {
                bb->Update(g);
            }
        }
    }
}


std::vector<std::vector<Block *>>
Level::BuildBlocks(std::vector<BlockType> types, sf::Texture *cementTexture, sf::Texture *brickTexture) {
    std::vector<std::vector<Block *>> blocks;
    for (int i = 0; i < LEVEL_WIDTH_IN_BLOCKS; i++) {
        blocks.emplace_back();
        for (int j = 0; j < LEVEL_HEIGHT_IN_BLOCKS; j++) {
            blocks[i].push_back(nullptr);
        }
    }

    for (int i = 0; i < types.size(); i++) {
        BlockType bt = types[i];

        int x = i % LEVEL_HEIGHT_IN_BLOCKS;
        int y = i / LEVEL_WIDTH_IN_BLOCKS;
        switch (bt) {
            case B:
                blocks[x][y] = new Block(brickTexture, Level::BlocksToDisplayPosition(sf::Vector2i(x, y)), true);
                break;
            case C:
                blocks[x][y] = new Block(cementTexture, Level::BlocksToDisplayPosition(sf::Vector2i(x, y)), false);
                break;
        }
    }
    return blocks;
}

Block *Level::AreBoundsIntersectBlock(sf::FloatRect bounds, sf::Vector2i blockPosition) {
    if (blockPosition.x < 0 || blockPosition.y < 0 || blockPosition.x >= LEVEL_WIDTH_IN_BLOCKS ||
        blockPosition.y >= LEVEL_HEIGHT_IN_BLOCKS || blocks[blockPosition.x][blockPosition.y] == nullptr) {
        return nullptr;
    }

    if (bounds.intersects(blocks[blockPosition.x][blockPosition.y]->Sprite->getGlobalBounds())) {
        return blocks[blockPosition.x][blockPosition.y];
    }

    return nullptr;
}

std::vector<Block *> Level::AreBoundsIntersectBlocks(sf::FloatRect bounds) {
    sf::Vector2i position = DisplayToBlocksPosition(sf::Vector2f(bounds.left, bounds.top));
    bounds.top = bounds.top + 2;
    bounds.left = bounds.left + 2;
    bounds.width = bounds.width - 4;
    bounds.height = bounds.height - 4;

    std::vector<Block *> res = {};

    Block *b = AreBoundsIntersectBlock(bounds, sf::Vector2i(position.x, position.y));
    if (b != nullptr) {
        res.push_back(b);
    }

    Block *bLeft = AreBoundsIntersectBlock(bounds, sf::Vector2i(position.x - 1, position.y));
    if (bLeft != nullptr) {
        res.push_back(bLeft);
    }

    Block *bRight = AreBoundsIntersectBlock(bounds, sf::Vector2i(position.x + 1, position.y));
    if (bRight != nullptr) {
        res.push_back(bRight);
    }

    Block *bUp = AreBoundsIntersectBlock(bounds, sf::Vector2i(position.x, position.y - 1));
    if (bUp != nullptr) {
        res.push_back(bUp);
    }

    Block *bDown = AreBoundsIntersectBlock(bounds, sf::Vector2i(position.x, position.y + 1));
    if (bDown != nullptr) {
        res.push_back(bDown);
    }

    Block *bLeftUp = AreBoundsIntersectBlock(bounds, sf::Vector2i(position.x - 1, position.y - 1));
    if (bLeftUp != nullptr) {
        res.push_back(bLeftUp);
    }

    Block *bRightUp = AreBoundsIntersectBlock(bounds, sf::Vector2i(position.x + 1, position.y - 1));
    if (bRightUp != nullptr) {
        res.push_back(bRightUp);
    }

    Block *bLeftDown = AreBoundsIntersectBlock(bounds, sf::Vector2i(position.x - 1, position.y + 1));
    if (bLeftDown != nullptr) {
        res.push_back(bLeftDown);
    }

    Block *bRightDown = AreBoundsIntersectBlock(bounds, sf::Vector2i(position.x + 1, position.y + 1));
    if (bRightDown != nullptr) {
        res.push_back(bRightDown);
    }

    return res;
}
