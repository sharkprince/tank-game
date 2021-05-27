#include "../game.h"
#include "game_states.h"

MenuState::MenuState(Game *g) {
    this->game = g;
    menuSprite = new sf::Sprite();
    menuSprite->setTexture(*game->MenuTexture);
    menuSprite->setTextureRect(sf::IntRect(0, 0, 640, 360));
}

void MenuState::Update() {
    game->DrawSprite(menuSprite);
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