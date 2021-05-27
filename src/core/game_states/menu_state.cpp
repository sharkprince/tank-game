#include "../game.h"
#include "game_states.h"
#include "../../const/rotation.h"

MenuState::MenuState(Game *g) {
    this->game = g;
    menuSprite = new sf::Sprite();
    menuSprite->setTexture(*game->MenuTexture);
    menuSprite->setTextureRect(sf::IntRect(0, 0, 640, 360));

    menuItemSprite = new sf::Sprite();
    menuItemSprite->setTexture(*game->TankTexture);
    menuItemSprite->setRotation(RIGHT_ROTATION);
    menuItemSprite->setPosition(ITEM_BASE_POSITION_X, ITEM_BASE_POSITION_Y);
    menuItemSprite->setTextureRect(sf::IntRect(0, 0, 24, 24));

    currentMenuItem = 0;
}

void MenuState::Update() {
    game->DrawSprite(menuSprite);
    game->DrawSprite(menuItemSprite);
}

void MenuState::UpdateOnEvent(sf::Event e) {
    if (e.type != sf::Event::KeyPressed) return;

    switch (e.key.code) {
        case sf::Keyboard::Enter:
            switch (currentMenuItem) {
                case 0:
                    game->RunArcade(1);
                    break;
                case 1:
                    game->RunArcade(2);
                    break;
                case 2:
                    game->Close();
            }
            break;
        case sf::Keyboard::Down:
            GoNextItem();
            break;
        case sf::Keyboard::Up:
            GoPrevItem();
            break;
        case sf::Keyboard::Escape:
            game->Close();
            break;
    }
}

void MenuState::GoNextItem() {
    if (currentMenuItem == 2) {
        currentMenuItem = 0;
    } else {
        currentMenuItem++;
    }

    menuItemSprite->setPosition(ITEM_BASE_POSITION_X, ITEM_BASE_POSITION_Y + (currentMenuItem * ITEM_STEP_Y));
}

void MenuState::GoPrevItem() {
    if (currentMenuItem == 0) {
        currentMenuItem = 2;
    } else {
        currentMenuItem--;
    }

    menuItemSprite->setPosition(ITEM_BASE_POSITION_X, ITEM_BASE_POSITION_Y + (currentMenuItem * ITEM_STEP_Y));
}
