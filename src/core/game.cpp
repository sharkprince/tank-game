#include "core.h"
#include "game_states/game_states.h"

Game::Game() : clock(sf::Clock()),
               window(sf::VideoMode(200, 200), "Tank Game") {
    state = new MenuState();
    newState = nullptr;
}

void Game::runArcade() {
    if (newState != nullptr) return;
    newState = new ArcadeState();
}

void Game::checkForClose() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Game::start() {
    while (window.isOpen()) {
        checkForClose();

        if (newState != nullptr) {
            state = newState;
            newState = nullptr;
        }

        state->update(this);

        window.clear();
        window.display();
    }
}
