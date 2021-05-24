#ifndef TANK_GAME_GAME_STATES_H
#define TANK_GAME_GAME_STATES_H

#include "../../models/tank.h"

class MenuState : public GameState {
public:
    MenuState(Game *);

    void Update() override;

    void UpdateOnEvent(sf::Event) override;
};

class ArcadeState : public GameState {
public:
    ArcadeState(Game *, sf::Texture *);

    void Update() override;

    void UpdateOnEvent(sf::Event) override;

private:
    Tank *playerOneTank;
};

#endif //TANK_GAME_GAME_STATES_H
