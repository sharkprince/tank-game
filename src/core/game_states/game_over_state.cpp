#include "../game.h"
#include "game_states.h"
#include "../../const/rotation.h"

GameOverState::GameOverState(Game *g) {
    this->game = g;
    gameOverSprite = new sf::Sprite();
    gameOverSprite->setTexture(*game->GameOverTexture);
    gameOverSprite->setTextureRect(sf::IntRect(0, 0, 640, 360));
}

void GameOverState::Update() {
    game->DrawSprite(gameOverSprite);
}

void GameOverState::UpdateOnEvent(sf::Event e) {
    if (e.type != sf::Event::KeyPressed) return;

    switch (e.key.code) {
        case sf::Keyboard::Enter:
        case sf::Keyboard::Escape:
            game->RunMenu();
            break;
    }
}