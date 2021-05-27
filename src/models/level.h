#ifndef TANK_GAME_LEVEL_H
#define TANK_GAME_LEVEL_H


#include <vector>
#include "block.h"
#include "tank.h"

enum BlockType {
    B,
    E,
    C,
    W,
    G,
};

class Level {
public:
    static const std::vector<sf::Vector2f> PlayerSpawnPoints;
    static const std::vector<sf::Vector2f> EnemySpawnPoints;

    static sf::Vector2f BlocksToDisplayPosition(sf::Vector2i position);

    static sf::Vector2i DisplayToBlocksPosition(sf::Vector2f position);

    static sf::Vector2i DisplayToBlocksTankPosition(sf::FloatRect position);

    static std::vector<std::vector<Block *>>
    BuildBlocks(std::vector<BlockType> types, sf::Texture *cementTexture, sf::Texture *brickTexture);

    Level(std::vector<std::vector<Block *>>, sf::Texture *enemyTankTexture, sf::Texture *bulletTexture,
          int enemiesCount);

    void Update(Game *g);

    Block *AreBoundsIntersectBlock(sf::FloatRect bounds, sf::Vector2i blockPosition);

    Tank *AreBoundsIntersectTank(sf::FloatRect bounds, sf::Vector2i tankPosition);

    std::vector<Block *> AreBoundsIntersectBlocks(sf::FloatRect bounds);

    std::vector<Tank *> AreBoundsIntersectTanks(sf::FloatRect bounds);

    std::vector<Tank *> Enemies;
    int EnemiesToKillCount;

    std::vector<std::vector<Tank *>> Tanks;

    constexpr static int LEVEL_WIDTH_IN_BLOCKS = 15;
    constexpr static int LEVEL_HEIGHT_IN_BLOCKS = 15;
private:
    std::vector<std::vector<Block *>> blocks;

    sf::Texture *enemyTankTexture;

    sf::Texture *bulletTexture;

    constexpr static float POSITION_X = 140.f;
    constexpr static float POSITION_Y = 0.f;
    constexpr static int MAX_ENEMY_TANKS_COUNT = 5;
};


#endif //TANK_GAME_LEVEL_H
