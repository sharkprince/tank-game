#ifndef TANK_GAME_GAME_STATES_H
#define TANK_GAME_GAME_STATES_H

#include "../../models/tank.h"
#include "../../models/block.h"
#include "../../models/level.h"

class MenuState : public GameState {
public:
    MenuState(Game *);

    void Update() override;

    void UpdateOnEvent(sf::Event) override;
};

class ArcadeState : public GameState {
public:
    ArcadeState(Game *);

    void Update() override;

    void UpdateOnEvent(sf::Event) override;

private:
    Tank *playerOneTank;
    Level *level;
};

#endif //TANK_GAME_GAME_STATES_H
