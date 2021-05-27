#include "game.h"
#include "game_states/game_states.h"

Game::Game() : clock(sf::Clock()),
               window(sf::VideoMode(640, 360), "Tank Game") {
    state = nullptr;
    newState = nullptr;

    MenuTexture = new sf::Texture();
    TankTexture = new sf::Texture();

    BulletTexture = new sf::Texture();
    BricksTexture = new sf::Texture();
    CementTexture = new sf::Texture();
    EnemyTankTexture = new sf::Texture();
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
        bool isBulletTextureLoaded = BulletTexture->loadFromFile("src/textures/bullet.png");
        if (!isBulletTextureLoaded) return;

        bool isBricksTextureLoaded = BricksTexture->loadFromFile("src/textures/bricks.png");
        if (!isBricksTextureLoaded) return;

        bool isCementTextureLoaded = CementTexture->loadFromFile("src/textures/cement.png");
        if (!isCementTextureLoaded) return;

        bool isEnemyTankTextureLoaded = EnemyTankTexture->loadFromFile("src/textures/enemy_tank.png");
        if (!isEnemyTankTextureLoaded) return;

        areArcadeTexturesLoaded = true;
    }

    newState = new ArcadeState(this);
}

void Game::RunMenu() {
    if (newState != nullptr) return;

    if (!areMenuTexturesLoaded) {
        bool isTankTextureLoaded = TankTexture->loadFromFile("src/textures/player_tank.png");
        if (!isTankTextureLoaded) return;

        bool isMenuTextureLoaded = MenuTexture->loadFromFile("src/textures/menu.png");
        if (!isMenuTextureLoaded) return;

        areMenuTexturesLoaded = true;
    }

    newState = new MenuState(this);
}

void Game::Close() {
    window.close();
}