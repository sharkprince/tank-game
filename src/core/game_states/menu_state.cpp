#include "../game.h"
#include "game_states.h"

MenuState::MenuState(Game *g) {
    this->game = g;
}

void MenuState::Update() {
}

void MenuState::UpdateOnEvent(sf::Event e) {
    if (e.type != sf::Event::KeyPressed) return;

    switch (e.key.code) {
        case sf::Keyboard::Enter:
            game->RunArcade();
            break;
        case sf::Keyboard::Escape:
            game->Close();
            break;
    }
}