#ifndef TANK_GAME_LEVELS_H
#define TANK_GAME_LEVELS_H

#include "../models/level.h"
#include "../models/block.h"

Level *createNewLevelOne(sf::Texture *waterTexture, sf::Texture *grassTexture, sf::Texture *cementTexture,
                         sf::Texture *brickTexture);

Level *createNewLevelTwo(sf::Texture *waterTexture, sf::Texture *grassTexture, sf::Texture *cementTexture,
                         sf::Texture *brickTexture);

Level *createNewLevelThree(sf::Texture *waterTexture, sf::Texture *grassTexture, sf::Texture *cementTexture,
                         sf::Texture *brickTexture);

#endif
