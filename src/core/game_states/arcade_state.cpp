#include "../game.h"
#include "game_states.h"
#include "../../const/rotation.h"
#include "../../levels/level_one.h"

ArcadeState::ArcadeState(Game *g) {
    this->game = g;
    playerOneTank = new Tank(Level::PlayerSpawnPoints[0], game->TankTexture, g->BulletTexture);
    level = createNewLevelOne(game->EnemyTankTexture, game->BulletTexture, game->CementTexture, game->BricksTexture);
}

void ArcadeState::Update() {
    level->Tanks = {};
    for (int i = 0; i < Level::LEVEL_WIDTH_IN_BLOCKS; i++) {
        level->Tanks.emplace_back();
        for (int j = 0; j < Level::LEVEL_HEIGHT_IN_BLOCKS; j++) {
            level->Tanks[i].push_back(nullptr);
        }
    }

    std::vector<Tank *> playerTanks = {};

    if (playerOneTank != nullptr) {
        auto position = Level::DisplayToBlocksTankPosition(playerOneTank->TankSprite.getGlobalBounds());
        level->Tanks[position.x][position.y] = playerOneTank;
        playerTanks.push_back(playerOneTank);
    }

//    if (playerTwoTank != nullptr) {
//        auto position = DisplayToBlocksTankPosition(playerTwoTank->TankSprite.getGlobalBounds());
//        tanks[position.x][position.y] = playerTwoTank;
//        playerTanks.push_back(playerTwoTank);
//    }

    for (Tank *e: level->Enemies) {
        auto position = Level::DisplayToBlocksTankPosition(e->TankSprite.getGlobalBounds());
        level->Tanks[position.x][position.y] = e;
    }

    if (playerOneTank != nullptr) {
        auto position = Level::DisplayToBlocksTankPosition(playerOneTank->TankSprite.getGlobalBounds());
        level->Tanks[position.x][position.y] = nullptr;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            auto bounds = playerOneTank->GetGoRightBounds(game->ElapsedSeconds);
            if (level->AreBoundsIntersectBlocks(bounds).empty() && level->AreBoundsIntersectTanks(bounds).empty()) {
                playerOneTank->GoRight(game->ElapsedSeconds);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            auto bounds = playerOneTank->GetGoDownBounds(game->ElapsedSeconds);
            if (level->AreBoundsIntersectBlocks(bounds).empty() && level->AreBoundsIntersectTanks(bounds).empty()) {
                playerOneTank->GoDown(game->ElapsedSeconds);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            auto bounds = playerOneTank->GetGoLeftBounds(game->ElapsedSeconds);
            if (level->AreBoundsIntersectBlocks(bounds).empty() && level->AreBoundsIntersectTanks(bounds).empty()) {
                playerOneTank->GoLeft(game->ElapsedSeconds);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            auto bounds = playerOneTank->GetGoUpBounds(game->ElapsedSeconds);
            if (level->AreBoundsIntersectBlocks(bounds).empty() && level->AreBoundsIntersectTanks(bounds).empty()) {
                playerOneTank->GoUp(game->ElapsedSeconds);
            }
        }
        level->Tanks[position.x][position.y] = playerOneTank;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            playerOneTank->Shoot();
        }

        for (int i = 0; i < playerOneTank->Bullets.size(); i++) {
            Bullet *b = playerOneTank->Bullets[i];
            sf::FloatRect bounds = b->Sprite.getGlobalBounds();

            bool isNeedToDeleteBullet = false;

            for (int j = 0; j < level->Enemies.size(); j++) {
                if (bounds.intersects(level->Enemies[j]->TankSprite.getGlobalBounds())) {
                    level->Enemies.erase(level->Enemies.begin() + j);
                    isNeedToDeleteBullet = true;
                }
            }

            std::vector<Block *> hitBlocks = level->AreBoundsIntersectBlocks(bounds);
            if (!hitBlocks.empty()) {
                for (Block *bb:hitBlocks) {
                    bb->Hit(ReverseRotation(b->Sprite.getRotation()));
                }
                isNeedToDeleteBullet = true;
            }

            if (isNeedToDeleteBullet) {
                playerOneTank->Bullets.erase(playerOneTank->Bullets.begin() + i);
            }
        }

        playerOneTank->Update(game);
    }

    level->Update(game);

    for (auto e: level->Enemies) {
        for (int i = 0; i < e->Bullets.size(); ++i) {
            sf::FloatRect bounds = e->Bullets[i]->Sprite.getGlobalBounds();
            if (playerOneTank != nullptr) {
                if (bounds.intersects(playerOneTank->TankSprite.getGlobalBounds())) {
                    playerOneTank = nullptr;
                }
            }
        }
    }


    if (playerOneTank == nullptr) {
        for (sf::Vector2f sp:Level::PlayerSpawnPoints) {
            sf::FloatRect rect = sf::FloatRect(sp.x - 12, sp.y - 12, 24, 24);
            auto res = level->AreBoundsIntersectTanks(rect);
            if (res.empty()) {
                playerOneTank = new Tank(sp, game->TankTexture, game->BulletTexture);

                auto position = Level::DisplayToBlocksTankPosition(playerOneTank->TankSprite.getGlobalBounds());
                level->Tanks[position.x][position.y] = playerOneTank;

                break;
            }
        }
    }

}

void ArcadeState::UpdateOnEvent(sf::Event e) {
    if (e.type != sf::Event::KeyPressed) return;

    switch (e.key.code) {
        case sf::Keyboard::Escape:
            game->RunMenu();
            break;
    }
}
