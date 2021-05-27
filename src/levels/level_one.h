#ifndef TANK_GAME_LEVEL_ONE_H
#define TANK_GAME_LEVEL_ONE_H

#include "../models/level.h"
#include "../models/block.h"

Level *createNewLevelOne(sf::Texture *enemyTankTexture, sf::Texture *bulletTexture, sf::Texture *cementTexture,
                         sf::Texture *brickTexture);

#endif
