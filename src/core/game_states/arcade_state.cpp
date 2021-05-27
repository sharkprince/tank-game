#include "../game.h"
#include "game_states.h"
#include "../../const/rotation.h"
#include "../../levels/level_one.h"

ArcadeState::ArcadeState(Game *g) {
    this->game = g;
    playerOneTank = new Tank(sf::Vector2f(463.5f, 323.5f), game->TankTexture, g->BulletTexture);
    level = createNewLevelOne(game->CementTexture, game->BricksTexture);
}

void ArcadeState::Update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (level->AreBoundsIntersectBlocks(playerOneTank->GetGoRightBounds(game->ElapsedSeconds)).empty()) {
            playerOneTank->GoRight(game->ElapsedSeconds);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (level->AreBoundsIntersectBlocks(playerOneTank->GetGoDownBounds(game->ElapsedSeconds)).empty()) {
            playerOneTank->GoDown(game->ElapsedSeconds);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (level->AreBoundsIntersectBlocks(playerOneTank->GetGoLeftBounds(game->ElapsedSeconds)).empty()) {
            playerOneTank->GoLeft(game->ElapsedSeconds);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (level->AreBoundsIntersectBlocks(playerOneTank->GetGoUpBounds(game->ElapsedSeconds)).empty()) {
            playerOneTank->GoUp(game->ElapsedSeconds);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        playerOneTank->Shoot();
    }


    for (int i = 0; i < playerOneTank->Bullets.size(); i++) {
        Bullet *b = playerOneTank->Bullets[i];
        std::vector<Block *> hitBlocks = level->AreBoundsIntersectBlocks(b->Sprite.getGlobalBounds());
        if (hitBlocks.empty()) {
            continue;
        }
        for (Block *bb:hitBlocks) {
            bb->Hit(ReverseRotation(b->Sprite.getRotation()));
        }
        playerOneTank->Bullets.erase(playerOneTank->Bullets.begin() + i);
    }

    playerOneTank->Update(game);
    level->Update(game);

}

void ArcadeState::UpdateOnEvent(sf::Event e) {
    if (e.type != sf::Event::KeyPressed) return;

    switch (e.key.code) {
        case sf::Keyboard::Escape:
            game->RunMenu();
            break;
    }
}
