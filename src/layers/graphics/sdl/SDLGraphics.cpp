#include "layers/graphics/sdl/SDLGraphics.h"
#include <iostream>
#include <list>

using namespace layers;

std::list<std::string> imageFilenames = {
    "Backdrop13.jpg",
    "Color-1.png",
    "Color-2.png",
    "Color-3.png",
    "Color-4.png",
    "Color-5.png",
    "board_back.png",
};

void SDLGraphics::initialize() {
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("error initializing SDL Graphics: %s\n", SDL_GetError());
    }
    window = SDL_CreateWindow("Jewelry",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, 0);

    /* We must call SDL_CreateRenderer in order for draw calls to affect this window. */
    renderer = SDL_CreateRenderer(window, -1, 0);

    //Update the surface
    SDL_UpdateWindowSurface(window);

    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
        printf("error initializing Image loader: %s\n", IMG_GetError());
    }

    for (std::string imgFilename : imageFilenames) {
        loadImage(imgFilename);
    }

}

void SDLGraphics::clear() const {
    SDL_RenderClear(renderer);
}

void SDLGraphics::render() const {
    SDL_RenderPresent(renderer);
}

void SDLGraphics::loadImage(const std::string filename) {
    Image* image = new Image(std::string("assets/image/").append(filename), 1, 1);

    //Load image at specified path
    SDL_Texture* loadedTexture = IMG_LoadTexture(renderer, image->getFilename().c_str());

    if (loadedTexture == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", image->getFilename().c_str(), IMG_GetError());
    }
    else
    {

        int w, h;
        SDL_QueryTexture(loadedTexture, NULL, NULL, &w, &h);

        image->setWidth(w);
        image->setHeight(h);

        images->insert(std::pair<Image*, SDL_Texture*>(image, loadedTexture));
        imageNames->insert(std::pair<std::string, Image*>(filename, image));

    }
}

void SDLGraphics::drawImage(const std::string name, int x, int y) const {

    drawImage(imageNames->at(name), x, y);

}

void SDLGraphics::drawImage(const Image* image, const int x, const int y) const {

    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = image->getWidth();
    dest.h = image->getHeight();

    // copy the texture to the rendering context
    SDL_RenderCopy(renderer, images->at(image), NULL, &dest);

}

void SDLGraphics::drawImage(const std::string name, const int x, const int y, const Viewport viewport) const {

    drawImage(imageNames->at(name), x, y, viewport);

}

void SDLGraphics::drawImage(const Image* image, const int x, const int y, const Viewport viewport) const {

    SDL_Rect rectViewport;
    rectViewport.x = viewport.x;
    rectViewport.y = viewport.y;
    rectViewport.w = viewport.width;
    rectViewport.h = viewport.height;

    SDL_RenderSetViewport(renderer, &rectViewport);

    drawImage(image, x, y);

    SDL_RenderSetViewport(renderer, NULL);

}

const Image* SDLGraphics::getImage(const std::string filename) {

    if (imageNames->find(filename) == imageNames->end()) {
        loadImage(filename);
    }

    return imageNames->at(filename);

}

SDLGraphics* SDLGraphics::getGraphics(int width, int height) {
	SDLGraphics* graphics = new SDLGraphics(width, height);
	graphics->initialize();
	return graphics;
}

void SDLGraphics::onClose() const {
    for (const auto& img : *images) {
        SDL_DestroyTexture(img.second);
    }

    // Destroy renderer
    SDL_DestroyRenderer(renderer);
    
    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystem
    SDL_VideoQuit();
}