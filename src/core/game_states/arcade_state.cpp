#include "../game.h"
#include "game_states.h"

ArcadeState::ArcadeState(Game *g, sf::Texture *tankTexture) {
    this->game = g;
    playerOneTank = new Tank(tankTexture, &g->BulletTexture);
}

void ArcadeState::Update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        playerOneTank->GoRight(game->ElapsedSeconds);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        playerOneTank->GoDown(game->ElapsedSeconds);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        playerOneTank->GoLeft(game->ElapsedSeconds);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        playerOneTank->GoUp(game->ElapsedSeconds);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        playerOneTank->Shoot(game->ElapsedSeconds);
    }

    playerOneTank->Update(game);
}

void ArcadeState::UpdateOnEvent(sf::Event e) {
    if (e.type != sf::Event::KeyPressed) return;

    switch (e.key.code) {
        case sf::Keyboard::Escape:
            game->RunMenu();
            break;
    }
}
