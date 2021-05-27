#include "../game.h"
#include "game_states.h"
#include "../../const/rotation.h"
#include "../../levels/levels.h"

ArcadeState::ArcadeState(Game *g, int playersCount) {
    this->game = g;

    elapsedFromGameOver = 0;

    playerOneTank = new Tank(Level::PlayerSpawnPoints[0], game->TankTexture, g->BulletTexture, g->ExplosionTexture);
    playerOneLivesCount = 3;
    playerOneLiveSprites = {
            new sf::Sprite(*g->HealthTexture, sf::IntRect(0, 0, 17, 17)),
            new sf::Sprite(*g->HealthTexture, sf::IntRect(0, 0, 17, 17)),
            new sf::Sprite(*g->HealthTexture, sf::IntRect(0, 0, 17, 17)),
    };
    playerOneLiveSprites[0]->setPosition(540.f, 171.5f);
    playerOneLiveSprites[1]->setPosition(557.f, 171.5f);
    playerOneLiveSprites[2]->setPosition(574.f, 171.5f);


    playerTwoLiveSprites = {};

    if (playersCount == 2) {
        playerTwoTank = new Tank(Level::PlayerSpawnPoints[1], game->TankTwoTexture, g->BulletTexture,
                                 g->ExplosionTexture);
        playerTwoLivesCount = 3;
        playerTwoLiveSprites = {
                new sf::Sprite(*g->HealthTexture, sf::IntRect(0, 0, 17, 17)),
                new sf::Sprite(*g->HealthTexture, sf::IntRect(0, 0, 17, 17)),
                new sf::Sprite(*g->HealthTexture, sf::IntRect(0, 0, 17, 17)),
        };
        playerTwoLiveSprites[0]->setPosition(46.f, 171.5f);
        playerTwoLiveSprites[1]->setPosition(63.f, 171.5f);
        playerTwoLiveSprites[2]->setPosition(80.f, 171.5f);
    } else {
        playerTwoTank = nullptr;
        playerTwoLivesCount = -1;
    }
    level = createNewLevelOne(game->WaterTexture, game->GrassTexture, game->CementTexture, game->BricksTexture);

    levelCount = 1;
    isLevelLoaderDisplaying = true;
    levelDisplay = new sf::Sprite();
    levelDisplay->setTexture(*g->LevelOneTexture);
    levelDisplay->setTextureRect(sf::IntRect(0, 0, 640, 360));
}

void ArcadeState::Update() {
    if (isLevelLoaderDisplaying) {
        elapsedFromGameOver += game->ElapsedSeconds;
        if (elapsedFromGameOver > 1.5f) {
            isLevelLoaderDisplaying = false;
            elapsedFromGameOver = 0;
        }
        game->DrawSprite(levelDisplay);
        return;
    }

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

    for (auto s: playerOneLiveSprites) {
        game->DrawSprite(s);
    }

    for (auto s: playerTwoLiveSprites) {
        game->DrawSprite(s);
    }

    for (auto e: level->Enemies) {
        for (int i = 0; i < e->Bullets.size(); ++i) {
            sf::FloatRect bounds = e->Bullets[i]->Sprite.getGlobalBounds();
            if (playerOneTank != nullptr) {
                if (bounds.intersects(playerOneTank->TankSprite->getGlobalBounds())) {
                    if (playerOneTank->Destroy()) {
                        playerOneLivesCount--;
                        if (!playerOneLiveSprites.empty()) {
                            playerOneLiveSprites.pop_back();
                        }
                    }
                }
            }
            if (playerTwoTank != nullptr) {
                if (bounds.intersects(playerTwoTank->TankSprite->getGlobalBounds())) {
                    if (playerTwoTank->Destroy()) {
                        playerTwoLivesCount--;
                        if (!playerTwoLiveSprites.empty()) {
                            playerTwoLiveSprites.pop_back();
                        }
                    }
                }
            }
        }
    }

    if (playerTwoLivesCount <= -1 && playerOneLivesCount <= -1) {
        elapsedFromGameOver += game->ElapsedSeconds;
        if (elapsedFromGameOver >= 1) {
            game->RunGameOver();
        }
    }


    if (playerOneTank == nullptr && playerOneLivesCount > -1) {
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

    if (playerTwoTank == nullptr && playerTwoLivesCount > -1) {
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

    if (level->Enemies.empty() && level->EnemiesToKillCount == 0 && !isLevelLoaderDisplaying) {
        if (levelCount == 3) {
            levelCount = 1;
        } else {
            levelCount++;
        }
        if (playerOneTank != nullptr) {
            playerOneTank->TankSprite->setPosition(Level::PlayerSpawnPoints[0].x, Level::PlayerSpawnPoints[0].y);
        }
        if (playerTwoTank != nullptr) {
            playerTwoTank->TankSprite->setPosition(Level::PlayerSpawnPoints[1].x, Level::PlayerSpawnPoints[0].y);
        }
        switch (levelCount) {
            case 1:
                levelDisplay->setTexture(*game->LevelOneTexture);
                level = createNewLevelOne(game->WaterTexture, game->GrassTexture, game->CementTexture,
                                          game->BricksTexture);
                break;
            case 2:
                levelDisplay->setTexture(*game->LevelTwoTexture);
                level = createNewLevelTwo(game->WaterTexture, game->GrassTexture, game->CementTexture,
                                          game->BricksTexture);
                break;
            case 3:
                levelDisplay->setTexture(*game->LevelThreeTexture);
                level = createNewLevelThree(game->WaterTexture, game->GrassTexture, game->CementTexture, game->BricksTexture);
                break;
        }
        isLevelLoaderDisplaying = true;
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
