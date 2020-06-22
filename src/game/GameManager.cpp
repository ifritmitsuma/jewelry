#include "game/GameManager.h"
#include "layers/LayerManager.h"
#include "game/board/BoardManager.h"
#include "layers/graphics/GraphicsManager.h"
#include "layers/input/InputManager.h"
#include "game/board/ScoreManager.h"
#include "layers/audio/AudioManager.h"
#include "game/MainMenuManager.h"

bool GameManager::quit = false;

GamePhase GameManager::phase = GamePhase::LEVEL;

void GameManager::initialize() {

    preparePhase(GamePhase::MAIN_MENU);

}

void GameManager::preparePhase(GamePhase phase) {

    GameManager::phase = phase;

    switch (phase) {

    case GamePhase::MAIN_MENU:

        layers::GraphicsManager::createNewViewport(graphics::ViewportType::MENU, 412, 500, 200, 130);

        layers::AudioManager::resume("song21.mp3", true);

        break;
    case GamePhase::LEVEL:
    {

        layers::GraphicsManager::createNewViewport(graphics::ViewportType::BOARD, 100, 100, 650, 650);

        layers::GraphicsManager::createNewViewport(graphics::ViewportType::SIDEBAR, 770, 100, 250, 650);

        board::BoardManager::initialize();

        layers::AudioManager::resume("song18.mp3", true);
        
        break;
    }
    case GamePhase::PAUSED:

        break;

    default:

        break;

    }

}

void GameManager::update() {

    //layers::GraphicsManager::clear();

    layers::InputManager::poll();

    layers::GraphicsManager::drawImage("Backdrop13.jpg", 0, 0);

    Image* logo = layers::GraphicsManager::getImage("logo.png");

    switch (phase) {
    
    case GamePhase::MAIN_MENU:

        logo->setWidth(800);
        logo->setHeight(300);

        layers::GraphicsManager::drawImage(logo, 112, 200);

        MainMenuManager::update();

        MainMenuManager::drawMainMenu();

        break;

    case GamePhase::LEVEL:
    {

        logo->setWidth(200);
        logo->setHeight(75);

        layers::GraphicsManager::drawImage(logo, 0, 0, layers::GraphicsManager::getViewport(ViewportType::SIDEBAR));

        board::BoardManager::update();

        board::BoardManager::drawBoard();

        board::BoardManager::drawSidebar();

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
    MainMenuManager::free();

}

void GameManager::handleMouse(const input::MouseInputType type, const int x, const int y) {

    int vX = x;
    int vY = y;

    Viewport viewport = layers::GraphicsManager::getViewportForCoordinate(&vX, &vY);

    const ViewportType vType = viewport.name;


    switch (phase) {
    case GamePhase::LEVEL:
        board::BoardManager::handleMouse(type, vX, vY, vType);
        break;
    case GamePhase::MAIN_MENU:
        MainMenuManager::handleMouse(type, vX, vY, vType);
        break;
    default:
        break;
    }

}

void GameManager::changePhase(GamePhase phase, bool pauseMusic) {
    if (pauseMusic) {
        layers::AudioManager::pauseMusic();
    } else {
        layers::AudioManager::stopMusic();
    }
    layers::GraphicsManager::clear();
    layers::GraphicsManager::clearViewports();
    preparePhase(phase);
}