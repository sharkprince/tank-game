#include "game.h"
#include "game_states/game_states.h"

Game::Game() : clock(sf::Clock()),
               window(sf::VideoMode(640, 360), "Tank Game") {
    state = nullptr;
    newState = nullptr;

    MenuTexture = new sf::Texture();
    TankTexture = new sf::Texture();
    TankTwoTexture = new sf::Texture();

    BulletTexture = new sf::Texture();
    BricksTexture = new sf::Texture();
    CementTexture = new sf::Texture();
    EnemyTankTexture = new sf::Texture();
    ExplosionTexture = new sf::Texture();
    GameOverTexture = new sf::Texture();
    GrassTexture = new sf::Texture();
    HealthTexture = new sf::Texture();
    LevelOneTexture = new sf::Texture();
    LevelTwoTexture = new sf::Texture();
    LevelThreeTexture = new sf::Texture();
    WaterTexture = new sf::Texture();
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

void Game::RunArcade(int playersCount) {
    if (newState != nullptr) return;

    if (!areArcadeTexturesLoaded) {
        bool isTankTwoTextureLoaded = TankTwoTexture->loadFromFile("src/textures/player_tank2.png");
        if (!isTankTwoTextureLoaded) return;

        bool isBulletTextureLoaded = BulletTexture->loadFromFile("src/textures/bullet.png");
        if (!isBulletTextureLoaded) return;

        bool isBricksTextureLoaded = BricksTexture->loadFromFile("src/textures/bricks.png");
        if (!isBricksTextureLoaded) return;

        bool isCementTextureLoaded = CementTexture->loadFromFile("src/textures/cement.png");
        if (!isCementTextureLoaded) return;

        bool isEnemyTankTextureLoaded = EnemyTankTexture->loadFromFile("src/textures/enemy_tank.png");
        if (!isEnemyTankTextureLoaded) return;

        bool isExplosionTextureLoaded = ExplosionTexture->loadFromFile("src/textures/explosion.png");
        if (!isExplosionTextureLoaded) return;

        bool isGameOverTextureLoaded = GameOverTexture->loadFromFile("src/textures/game_over.png");
        if (!isGameOverTextureLoaded) return;

        bool isGrassTextureLoaded = GrassTexture->loadFromFile("src/textures/grass.png");
        if (!isGrassTextureLoaded) return;

        bool isHealthTextureLoaded = HealthTexture->loadFromFile("src/textures/health.png");
        if (!isHealthTextureLoaded) return;

        bool isLevelOneTextureLoaded = LevelOneTexture->loadFromFile("src/textures/level_1.png");
        if (!isLevelOneTextureLoaded) return;

        bool isLevelTwoTextureLoaded = LevelTwoTexture->loadFromFile("src/textures/level_2.png");
        if (!isLevelTwoTextureLoaded) return;

        bool isLevelThreeTextureLoaded = LevelThreeTexture->loadFromFile("src/textures/level_3.png");
        if (!isLevelThreeTextureLoaded) return;

        bool isWaterTextureLoaded = WaterTexture->loadFromFile("src/textures/water.png");
        if (!isWaterTextureLoaded) return;

        areArcadeTexturesLoaded = true;
    }

    newState = new ArcadeState(this, playersCount);
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

void Game::RunGameOver() {
    if (newState != nullptr) return;

    newState = new GameOverState(this);
}

void Game::Close() {
    window.close();
}