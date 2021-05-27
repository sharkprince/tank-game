#include "../game.h"
#include "game_states.h"
#include "../../const/rotation.h"
#include "../../levels/levels.h"

ArcadeState::ArcadeState(Game *g, int playersCount) {
    this->game = g;
    this->playersCount = playersCount;

    playerOneTank = new Tank(Level::PlayerSpawnPoints[0], game->TankTexture, g->BulletTexture, g->ExplosionTexture);
    if (playersCount == 2) {
        playerTwoTank = new Tank(Level::PlayerSpawnPoints[1], game->TankTwoTexture, g->BulletTexture,
                                 g->ExplosionTexture);
    } else {
        playerTwoTank = nullptr;
    }
    level = createNewLevelOne(game->WaterTexture, game->GrassTexture, game->CementTexture, game->BricksTexture);
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
        auto position = Level::DisplayToBlocksTankPosition(playerOneTank->TankSprite->getGlobalBounds());
        level->Tanks[position.x][position.y] = playerOneTank;
        playerTanks.push_back(playerOneTank);
    }

    if (playerTwoTank != nullptr) {
        auto position = Level::DisplayToBlocksTankPosition(playerTwoTank->TankSprite->getGlobalBounds());
        level->Tanks[position.x][position.y] = playerTwoTank;
        playerTanks.push_back(playerTwoTank);
    }

    for (Tank *e: level->Enemies) {
        auto position = Level::DisplayToBlocksTankPosition(e->TankSprite->getGlobalBounds());
        level->Tanks[position.x][position.y] = e;
    }

    if (playerOneTank != nullptr) {
        if (playerOneTank->GetIsDestroyed()) {
            playerOneTank->Update(game);
            if (playerOneTank->GetExplosionDuration() >= 1.5f) {
                playerOneTank = nullptr;
            }
        } else {
            auto position = Level::DisplayToBlocksTankPosition(playerOneTank->TankSprite->getGlobalBounds());
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
                playerOneTank->Shoot();
            }

            for (int i = 0; i < playerOneTank->Bullets.size(); i++) {
                Bullet *b = playerOneTank->Bullets[i];
                sf::FloatRect bounds = b->Sprite.getGlobalBounds();

                bool isNeedToDeleteBullet = false;

                for (int j = 0; j < level->Enemies.size(); j++) {
                    if (bounds.intersects(level->Enemies[j]->TankSprite->getGlobalBounds())) {
                        level->Enemies[j]->Destroy();
                        isNeedToDeleteBullet = true;
                    }
                }

                std::vector<Block *> hitBlocks = level->AreBoundsIntersectBlocks(bounds);
                if (!hitBlocks.empty()) {
                    for (Block *bb:hitBlocks) {
                        if (bb->GetIsDeep()) {
                            continue;
                        }
                        bb->Hit(ReverseRotation(b->Sprite.getRotation()));
                        isNeedToDeleteBullet = true;
                    }
                }

                if (isNeedToDeleteBullet) {
                    playerOneTank->Bullets.erase(playerOneTank->Bullets.begin() + i);
                }
            }

            playerOneTank->Update(game);
        }

    }

    if (playerTwoTank != nullptr) {
        if (playerTwoTank->GetIsDestroyed()) {
            playerTwoTank->Update(game);
            if (playerTwoTank->GetExplosionDuration() >= 1.5f) {
                playerTwoTank = nullptr;
            }
        } else {
            auto position = Level::DisplayToBlocksTankPosition(playerTwoTank->TankSprite->getGlobalBounds());
            level->Tanks[position.x][position.y] = nullptr;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                auto bounds = playerTwoTank->GetGoRightBounds(game->ElapsedSeconds);
                if (level->AreBoundsIntersectBlocks(bounds).empty() && level->AreBoundsIntersectTanks(bounds).empty()) {
                    playerTwoTank->GoRight(game->ElapsedSeconds);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                auto bounds = playerTwoTank->GetGoDownBounds(game->ElapsedSeconds);
                if (level->AreBoundsIntersectBlocks(bounds).empty() && level->AreBoundsIntersectTanks(bounds).empty()) {
                    playerTwoTank->GoDown(game->ElapsedSeconds);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                auto bounds = playerTwoTank->GetGoLeftBounds(game->ElapsedSeconds);
                if (level->AreBoundsIntersectBlocks(bounds).empty() && level->AreBoundsIntersectTanks(bounds).empty()) {
                    playerTwoTank->GoLeft(game->ElapsedSeconds);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                auto bounds = playerTwoTank->GetGoUpBounds(game->ElapsedSeconds);
                if (level->AreBoundsIntersectBlocks(bounds).empty() && level->AreBoundsIntersectTanks(bounds).empty()) {
                    playerTwoTank->GoUp(game->ElapsedSeconds);
                }
            }
            level->Tanks[position.x][position.y] = playerTwoTank;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
                playerTwoTank->Shoot();
            }

            for (int i = 0; i < playerTwoTank->Bullets.size(); i++) {
                Bullet *b = playerTwoTank->Bullets[i];
                sf::FloatRect bounds = b->Sprite.getGlobalBounds();

                bool isNeedToDeleteBullet = false;

                for (int j = 0; j < level->Enemies.size(); j++) {
                    if (bounds.intersects(level->Enemies[j]->TankSprite->getGlobalBounds())) {
                        level->Enemies[j]->Destroy();
                        isNeedToDeleteBullet = true;
                    }
                }

                std::vector<Block *> hitBlocks = level->AreBoundsIntersectBlocks(bounds);
                if (!hitBlocks.empty()) {
                    for (Block *bb:hitBlocks) {
                        if (bb->GetIsDeep()) {
                            continue;;
                        }
                        bb->Hit(ReverseRotation(b->Sprite.getRotation()));
                        isNeedToDeleteBullet = true;
                    }
                }

                if (isNeedToDeleteBullet) {
                    playerTwoTank->Bullets.erase(playerTwoTank->Bullets.begin() + i);
                }
            }

            playerTwoTank->Update(game);
        }

    }

    level->Update(game);

    for (auto e: level->Enemies) {
        for (int i = 0; i < e->Bullets.size(); ++i) {
            sf::FloatRect bounds = e->Bullets[i]->Sprite.getGlobalBounds();
            if (playerOneTank != nullptr) {
                if (bounds.intersects(playerOneTank->TankSprite->getGlobalBounds())) {
                    playerOneTank->Destroy();
                }
            }
            if (playerTwoTank != nullptr) {
                if (bounds.intersects(playerTwoTank->TankSprite->getGlobalBounds())) {
                    playerTwoTank->Destroy();
                }
            }
        }
    }


    if (playerOneTank == nullptr) {
        for (sf::Vector2f sp:Level::PlayerSpawnPoints) {
            sf::FloatRect rect = sf::FloatRect(sp.x - 12, sp.y - 12, 24, 24);
            auto res = level->AreBoundsIntersectTanks(rect);
            if (res.empty()) {
                playerOneTank = new Tank(sp, game->TankTexture, game->BulletTexture, game->ExplosionTexture);

                auto position = Level::DisplayToBlocksTankPosition(playerOneTank->TankSprite->getGlobalBounds());
                level->Tanks[position.x][position.y] = playerOneTank;

                break;
            }
        }
    }

    if (playerTwoTank == nullptr && playersCount == 2) {
        for (sf::Vector2f sp:Level::PlayerSpawnPoints) {
            sf::FloatRect rect = sf::FloatRect(sp.x - 12, sp.y - 12, 24, 24);
            auto res = level->AreBoundsIntersectTanks(rect);
            if (res.empty()) {
                playerTwoTank = new Tank(sp, game->TankTwoTexture, game->BulletTexture, game->ExplosionTexture);

                auto position = Level::DisplayToBlocksTankPosition(playerTwoTank->TankSprite->getGlobalBounds());
                level->Tanks[position.x][position.y] = playerTwoTank;

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
