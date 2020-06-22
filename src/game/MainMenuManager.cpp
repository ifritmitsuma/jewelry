#include "game/MainMenuManager.h"
#include "game/GameManager.h"
#include "game/GamePhase.h"
#include "layers/graphics/Color.h"
#include "layers/graphics/GraphicsManager.h"
#include "layers/graphics/Button.h"
#include <iostream>

int MainMenuManager::hover = 0;

void MainMenuManager::update() {
	// Nothing to do
}

void MainMenuManager::drawMainMenu() {

    Viewport viewport = layers::GraphicsManager::getViewport(ViewportType::MENU);
    
    int fontSize = 36;
    media::Text playText = { "Play", "Blader", fontSize };
    media::Text quitText = { "Quit", "Blader", fontSize };
    
    graphics::Button* play = new Button(1, playText);
    play->drawButton(0, 0, hover == 1, &viewport);

    graphics::Button* quit = new Button(1, quitText);
    quit->drawButton(0, 70, hover == 2, &viewport);

}

void MainMenuManager::handleMouse(const input::MouseInputType type, const int x, const int y, const ViewportType vType) {

    switch (vType) {
    case ViewportType::MENU: {
        int button = 0;

        if (y >= 0 && y <= 60) {
            // PLAY button
            button = 1;
        }

        if (y >= 70 && y <= 130) {
            // EXIT button
            button = 2;
        }

        if (button == 0) {
            hover = 0;
            return;
        }

        switch (type) {
        case input::MouseInputType::HOVER:
            hover = button;
            break;
        case input::MouseInputType::LEFT_BUTTON_DOWN:
            if (button == 1) {
                GameManager::changePhase(GamePhase::LEVEL);
            }
            else if (button == 2) {
                GameManager::quit = true;
            }
        default:
            hover = false;
            break;
        }

        break;
    }
    default:
        hover = 0;
        break;
    }

    

}

void MainMenuManager::free() {
}