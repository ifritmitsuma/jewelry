#include "GameManager.h"
#include "layers/LayerManager.h"
#include "board/BoardManager.h"
#include "layers/graphics/GraphicsManager.h"
#include "layers/input/InputManager.h"
#include "ScoreManager.h"

bool GameManager::quit = false;

GamePhase GameManager::phase = GamePhase::MAIN_MENU;

void GameManager::initialize() {

    layers::GraphicsManager::createNewViewport(graphics::ViewportType::BOARD, 100, 100, 650, 650);

    layers::GraphicsManager::createNewViewport(graphics::ViewportType::SCORE, 720, 100, 100, 20);

    ScoreManager::drawScore();

}

void GameManager::update() {

    layers::GraphicsManager::clear();

    layers::InputManager::poll();

    layers::GraphicsManager::drawImage("Backdrop13.jpg", 0, 0);

    switch (phase) {
    
    case GamePhase::MAIN_MENU:
    case GamePhase::LEVEL:
    {

        board::BoardManager::update();

        board::BoardManager::drawBoard();

        //ScoreManager::drawScore();

        break;
    }
    case GamePhase::PAUSED:
    
        break;
    
    default:
        
        break;
    
    }

    layers::GraphicsManager::render();

}

void GameManager::free() {

    layers::LayerManager::free();
    board::BoardManager::free();

}

void GameManager::handleMouse(const input::MouseInputType type, const int x, const int y) {

    int vX = x;
    int vY = y;

    Viewport viewport = layers::GraphicsManager::getViewportForCoordinate(&vX, &vY);

    const ViewportType vType = viewport.name;

    switch (vType) {
    case ViewportType::BOARD:
        board::BoardManager::handleMouse(type, vX, vY);
        break;
    default:
        break;
    }

}