#include "layers/graphics/GraphicsManager.h"
#include "layers/input/InputManager.h"
#include "layers/LayerManager.h"
#include "GameManager.h"
#include "board/BoardManager.h"

using namespace std;

int main(int argc, char** argv) {

    GameManager::initialize();

    while (!board::BoardManager::sweep());
    
    while (!GameManager::quit) {

        GameManager::update();

    }

    GameManager::free();

    return 0;
}
