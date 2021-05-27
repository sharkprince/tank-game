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

    void GoNextItem();

    void GoPrevItem();

private:
    sf::Sprite *menuSprite;
    sf::Sprite *menuItemSprite;

    int currentMenuItem;

    constexpr static float ITEM_BASE_POSITION_X = 224.f;
    constexpr static float ITEM_BASE_POSITION_Y = 190.f;
    constexpr static float ITEM_STEP_Y = 45.f;
};

class ArcadeState : public GameState {
public:
    ArcadeState(Game *, int);

    void Update() override;

    void UpdateOnEvent(sf::Event) override;

private:
    int playerOneLivesCount;
    int playerTwoLivesCount;

    Tank *playerOneTank;
    Tank *playerTwoTank;
    Level *level;
};

#endif //TANK_GAME_GAME_STATES_H
