#include "layers/graphics/GraphicsManager.h"
#include "layers/input/InputManager.h"
#include "layers/LayerManager.h"
#include "game/GameManager.h"

using namespace std;

int main(int argc, char** argv) {

    GameManager::initialize();
    
    while (!GameManager::quit) {

        GameManager::update();

    }

    GameManager::free();

    return 0;
}
