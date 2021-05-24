#include "game.h"
#include "game_states/game_states.h"

Game::Game() : clock(sf::Clock()),
               window(sf::VideoMode(360, 240), "Tank Game") {
    state = nullptr;
    newState = nullptr;
}

void Game::Start() {
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    clock.restart();

    this->RunMenu();

    while (window.isOpen()) {
        if (newState != nullptr) {
            state = newState;
            newState = nullptr;
        }

        window.clear();

        ElapsedSeconds = clock.restart().asSeconds();

        sf::Event e{};
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                this->Close();
            }

            this->state->UpdateOnEvent(e);
        }

        state->Update();

        window.display();
    }
}

void Game::DrawSprite(sf::Sprite *s) {
    window.draw(*s);
}

void Game::RunArcade() {
    if (newState != nullptr) return;

    if (!areArcadeTexturesLoaded) {
        bool isTankTextureLoaded = tankTexture.loadFromFile("src/textures/player_tank.png");
        if (!isTankTextureLoaded) return;

        bool isBulletTextureLoaded = BulletTexture.loadFromFile("src/textures/bullet.png");
        if (!isBulletTextureLoaded) return;

        areArcadeTexturesLoaded = true;
    }

    newState = new ArcadeState(this, &tankTexture);
}

void Game::RunMenu() {
    if (newState != nullptr) return;
    newState = new MenuState(this);
}

void Game::Close() {
    window.close();
}