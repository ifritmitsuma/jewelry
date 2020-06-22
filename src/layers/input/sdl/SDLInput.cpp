#include "layers/input/sdl/SDLInput.h"
#include "sdl/SDL.h"
#include "game/GameManager.h"
#include "layers/input/MouseInputType.h"

using namespace layers;

void SDLInput::poll() const {
    
    SDL_Event e;

    //Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        //User requests quit
        if (e.type == SDL_QUIT)
        {
            GameManager::quit = true;
        }
        else {
            
            if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {

                int x, y;

                SDL_GetMouseState(&x, &y);

                switch (e.type) {
                case SDL_MOUSEMOTION:
                    GameManager::handleMouse(input::MouseInputType::HOVER, x, y);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    GameManager::handleMouse(input::MouseInputType::LEFT_BUTTON_DOWN, x, y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    GameManager::handleMouse(input::MouseInputType::LEFT_BUTTON_UP, x, y);
                    break;
                default: break;
                }
            
            }
        }
    }
}

SDLInput* SDLInput::getInput() {
    SDLInput* input = new SDLInput();
    input->initialize();
    return input;
}

void SDLInput::initialize() {

}

void SDLInput::onClose() const {

}