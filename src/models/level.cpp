#include "level.h"
#include "../const/rotation.h"

#include <utility>
#include <cmath>

const std::vector<sf::Vector2f> Level::PlayerSpawnPoints = {
        sf::Vector2f(463.f, 323.f),
        sf::Vector2f(176.f, 323.f),
        sf::Vector2f(320.f, 323.f)
};

const std::vector<sf::Vector2f> Level::EnemySpawnPoints = {
        sf::Vector2f(463.f, 36.f),
        sf::Vector2f(176.f, 36.f),
        sf::Vector2f(320.f, 36.f)
};

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

sf::Vector2i Level::DisplayToBlocksTankPosition(sf::FloatRect position) {
    int x = std::lrint((position.left + 24 - POSITION_X) / Block::BLOCK_WIDTH_PIXELS);
    int y = std::lrint((position.top + 24 - POSITION_Y) / Block::BLOCK_HEIGHT_PIXELS);
    return sf::Vector2i(x, y);
}

Level::Level(std::vector<std::vector<Block *>> blocks, int enemiesCount) {
    this->blocks = std::move(blocks);
    EnemiesToKillCount = enemiesCount;
}

void Level::Update(Game *g) {

    for (int i = 0; i < Enemies.size(); i++) {
        Tank *e = Enemies[i];
        if (e->GetIsDestroyed()) {
            e->Update(g);
            if (e->GetExplosionDuration() >= 1.5f) {
                Enemies.erase(Enemies.begin() + i);
            }
            continue;
        }
        e->ElapsedRandMove += g->ElapsedSeconds;
        if (e->ElapsedRandMove < e->RandMoveLength) {
            auto position = DisplayToBlocksTankPosition(e->TankSprite->getGlobalBounds());
            Tanks[position.x][position.y] = nullptr;
            sf::FloatRect leftBounds = e->GetGoLeftBounds(g->ElapsedSeconds);
            sf::FloatRect upBounds = e->GetGoUpBounds(g->ElapsedSeconds);
            sf::FloatRect rightBounds = e->GetGoRightBounds(g->ElapsedSeconds);
            sf::FloatRect downBounds = e->GetGoDownBounds(g->ElapsedSeconds);
            switch (e->RandMove) {
                case 1:
                    if (AreBoundsIntersectBlocks(rightBounds).empty() && AreBoundsIntersectTanks(rightBounds).empty()) {
                        e->GoRight(g->ElapsedSeconds);
                    }
                    break;
                case 2:
                    if (AreBoundsIntersectBlocks(upBounds).empty() && AreBoundsIntersectTanks(upBounds).empty()) {
                        e->GoUp(g->ElapsedSeconds);
                    }
                    break;
                case 3:
                    if (AreBoundsIntersectBlocks(downBounds).empty() && AreBoundsIntersectTanks(downBounds).empty()) {
                        e->GoDown(g->ElapsedSeconds);
                    }
                    break;
                case 4:
                    if (AreBoundsIntersectBlocks(leftBounds).empty() && AreBoundsIntersectTanks(leftBounds).empty()) {
                        e->GoLeft(g->ElapsedSeconds);
                    }
                    break;
            }
            Tanks[position.x][position.y] = e;
        } else {
            e->Shoot();
            e->ElapsedRandMove = 0;
            e->RandMove = rand() % 5;
            e->RandMoveLength = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.8f - 0.5f)));;
        }

        for (int j = 0; j < e->Bullets.size(); j++) {
            Bullet *b = e->Bullets[j];
            sf::FloatRect bounds = b->Sprite.getGlobalBounds();

            bool isNeedToDeleteBullet = false;

            std::vector<Block *> hitBlocks = AreBoundsIntersectBlocks(bounds);
            if (!hitBlocks.empty()) {
                for (Block *bb:hitBlocks) {
                    bb->Hit(ReverseRotation(b->Sprite.getRotation()));
                }
                isNeedToDeleteBullet = true;
            }

            if (isNeedToDeleteBullet) {
                e->Bullets.erase(e->Bullets.begin() + j);
            }
        }

        e->Update(g);
    }

    for (const std::vector<Block *> &b:blocks) {
        for (Block *bb: b) {
            if (bb != nullptr) {
                bb->Update(g);
            }
        }
    }

    int enemiesToSpawnRaw = MAX_ENEMY_TANKS_COUNT - Enemies.size();
    if (enemiesToSpawnRaw <= 0) return;

    int enemiesToSpawn = enemiesToSpawnRaw > EnemiesToKillCount ? EnemiesToKillCount : enemiesToSpawnRaw;
    if (enemiesToSpawn <= 0) return;

    int enemiesToSpawnOnSpawnPoints = enemiesToSpawn > EnemySpawnPoints.size()
                                      ? EnemySpawnPoints.size()
                                      : enemiesToSpawn;

    int spawnedEnemiesCount = 0;
    for (int i = 0; i < enemiesToSpawnOnSpawnPoints; i++) {
        bool isSpawned = false;
        for (sf::Vector2f sp:EnemySpawnPoints) {
            sf::FloatRect rect = sf::FloatRect(sp.x - 12, sp.y - 12, 24, 24);
            auto res = AreBoundsIntersectTanks(rect);
            if (res.empty()) {
                Tank *newEnemy = new Tank(sp, g->EnemyTankTexture, g->BulletTexture, g->ExplosionTexture);
                Enemies.push_back(newEnemy);

                auto position = DisplayToBlocksTankPosition(newEnemy->TankSprite->getGlobalBounds());
                Tanks[position.x][position.y] = newEnemy;

                isSpawned = true;
                break;
            }
        }
        if (!isSpawned) {
            break;
        }
        spawnedEnemiesCount++;
    }
    EnemiesToKillCount -= spawnedEnemiesCount;
}


std::vector<std::vector<Block *>>
Level::BuildBlocks(std::vector<BlockType> types, sf::Texture *waterTexture, sf::Texture *grassTexture,
                   sf::Texture *cementTexture, sf::Texture *brickTexture) {
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
                blocks[x][y] = new Block(brickTexture, Level::BlocksToDisplayPosition(sf::Vector2i(x, y)), true, false,
                                         false);
                break;
            case C:
                blocks[x][y] = new Block(cementTexture, Level::BlocksToDisplayPosition(sf::Vector2i(x, y)), false,
                                         false, false);
                break;
            case G:
                blocks[x][y] = new Block(grassTexture, Level::BlocksToDisplayPosition(sf::Vector2i(x, y)), false, true,
                                         false);
                break;
            case W:
                blocks[x][y] = new Block(waterTexture, Level::BlocksToDisplayPosition(sf::Vector2i(x, y)), false, false,
                                         true);
                break;
        }
    }
    return blocks;
}

Block *Level::AreBoundsIntersectBlock(sf::FloatRect bounds, sf::Vector2i blockPosition) {
    if (blockPosition.x < 0 || blockPosition.y < 0 || blockPosition.x >= LEVEL_WIDTH_IN_BLOCKS ||
        blockPosition.y >= LEVEL_HEIGHT_IN_BLOCKS || blocks[blockPosition.x][blockPosition.y] == nullptr ||
        blocks[blockPosition.x][blockPosition.y]->GetIsSoft()) {
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


Tank *Level::AreBoundsIntersectTank(sf::FloatRect bounds, sf::Vector2i tankPosition) {
    if (tankPosition.x < 0 || tankPosition.y < 0 || tankPosition.x >= LEVEL_WIDTH_IN_BLOCKS ||
        tankPosition.y >= LEVEL_HEIGHT_IN_BLOCKS || Tanks[tankPosition.x][tankPosition.y] == nullptr) {
        return nullptr;
    }

    if (bounds.intersects(Tanks[tankPosition.x][tankPosition.y]->TankSprite->getGlobalBounds())) {
        return Tanks[tankPosition.x][tankPosition.y];
    }

    return nullptr;
}

std::vector<Tank *> Level::AreBoundsIntersectTanks(sf::FloatRect bounds) {
    sf::Vector2i position = DisplayToBlocksTankPosition(bounds);

    std::vector<Tank *> res = {};

    Tank *b = AreBoundsIntersectTank(bounds, sf::Vector2i(position.x, position.y));
    if (b != nullptr) {
        res.push_back(b);
    }

    Tank *bLeft = AreBoundsIntersectTank(bounds, sf::Vector2i(position.x - 1, position.y));
    if (bLeft != nullptr) {
        res.push_back(bLeft);
    }

    Tank *bRight = AreBoundsIntersectTank(bounds, sf::Vector2i(position.x + 1, position.y));
    if (bRight != nullptr) {
        res.push_back(bRight);
    }

    Tank *bUp = AreBoundsIntersectTank(bounds, sf::Vector2i(position.x, position.y - 1));
    if (bUp != nullptr) {
        res.push_back(bUp);
    }

    Tank *bDown = AreBoundsIntersectTank(bounds, sf::Vector2i(position.x, position.y + 1));
    if (bDown != nullptr) {
        res.push_back(bDown);
    }

    Tank *bLeftUp = AreBoundsIntersectTank(bounds, sf::Vector2i(position.x - 1, position.y - 1));
    if (bLeftUp != nullptr) {
        res.push_back(bLeftUp);
    }

    Tank *bRightUp = AreBoundsIntersectTank(bounds, sf::Vector2i(position.x + 1, position.y - 1));
    if (bRightUp != nullptr) {
        res.push_back(bRightUp);
    }

    Tank *bLeftDown = AreBoundsIntersectTank(bounds, sf::Vector2i(position.x - 1, position.y + 1));
    if (bLeftDown != nullptr) {
        res.push_back(bLeftDown);
    }

    Tank *bRightDown = AreBoundsIntersectTank(bounds, sf::Vector2i(position.x + 1, position.y + 1));
    if (bRightDown != nullptr) {
        res.push_back(bRightDown);
    }

    return res;
}