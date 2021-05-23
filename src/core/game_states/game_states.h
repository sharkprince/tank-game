#ifndef TANK_GAME_GAME_STATES_H
#define TANK_GAME_GAME_STATES_H

class MenuState : public GameState {
public:
    void update(Game *) override;
};

class ArcadeState : public GameState {
public:
    void update(Game *) override;
};

#endif //TANK_GAME_GAME_STATES_H
