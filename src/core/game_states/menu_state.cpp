#include "../core.h"
#include "game_states.h"

void MenuState::update(Game *g) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        g->runArcade();
    }
}