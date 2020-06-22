#include "layers/graphics/sdl/SDLGraphics.h"
#include <iostream>
#include <list>

using namespace layers;

Uint32 SCREEN_TICKS_PER_FRAME;
Uint32 startTicks = SDL_GetTicks();
Uint32 capTicks;
int countedFrames = 0;

std::list<std::string> fontNames = {
    "Blader"
};

std::list<int> fontSizes = {
    22, 36, 48, 72
};

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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    //Update the surface
    SDL_UpdateWindowSurface(window);

    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
        printf("error initializing Image loader: %s\n", IMG_GetError());
    }

    //Initialize SDL_ttf
    if (TTF_Init() < 0)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

    for (std::string imgFilename : imageFilenames) {
        loadImage(imgFilename);
    }

    for (std::string font : fontNames) {
        loadFont(font);
    }

}

void SDLGraphics::beforeRender() const {

    capTicks = SDL_GetTicks();

    float avgFPS = countedFrames / ((SDL_GetTicks() - startTicks) / 1000.0f);
    if (avgFPS > 2000000) {
        avgFPS = 0;
    }

}

void SDLGraphics::clear() const {

    SDL_RenderClear(renderer);

}

void SDLGraphics::render() const {
    SDL_RenderPresent(renderer);
    countedFrames++;
    capTicks = SDL_GetTicks() - capTicks;
    if (capTicks < SCREEN_TICKS_PER_FRAME) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - capTicks);
    }
    
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

        image->setWidth((float) w);
        image->setHeight((float) h);

        images->insert(std::pair<Image, SDL_Texture*>(*image, loadedTexture));
        imageNames->insert(std::pair<std::string, Image*>(filename, image));

    }
}

void SDLGraphics::loadFont(const std::string font) {

    std::string fontFileName = std::string("assets/font/").append(font + ".ttf");

    for (int size : fontSizes) {
        
        TTF_Font* gFont = TTF_OpenFont(fontFileName.c_str(), size);
        if (gFont == NULL)
        {
            printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        }
        else {

            fonts->insert(std::pair<std::string, TTF_Font*>(font + std::to_string(size), gFont));

        }

    }
}

void SDLGraphics::drawImage(const std::string name, const float x, const float y) const {

    drawImage(imageNames->at(name), x, y);

}

void SDLGraphics::drawImage(Image* image, const float x, const float y) const {

    SDL_FRect dest;
    dest.x = x;
    dest.y = y;
    dest.w = image->getWidth();
    dest.h = image->getHeight();

    // copy the texture to the rendering context
    SDL_RenderCopyF(renderer, images->at(*image), NULL, &dest);

}

void SDLGraphics::drawImage(const std::string name, const float x, const float y, const Viewport viewport) const {

    drawImage(imageNames->at(name), x, y, viewport);

}

void SDLGraphics::drawImage(Image* image, const float x, const float y, const Viewport viewport) const {

    SDL_Rect rectViewport;
    rectViewport.x = viewport.x;
    rectViewport.y = viewport.y;
    rectViewport.w = viewport.width;
    rectViewport.h = viewport.height;

    SDL_RenderSetViewport(renderer, &rectViewport);

    drawImage(image, x, y);

    SDL_RenderSetViewport(renderer, NULL);

}

void SDLGraphics::drawText(const Text text, const float x, const float y) const {

    SDL_Color color = { (Uint8) text.color.r, (Uint8) text.color.g, (Uint8) text.color.b, (Uint8) text.color.a };

    SDL_Surface* textureSurface = TTF_RenderText_Solid(fonts->at(text.font + std::to_string(text.size)), text.text.c_str(), color);

    SDL_FRect dest;
    dest.x = x;
    dest.y = y;
    dest.w = (float) textureSurface->w;
    dest.h = (float) textureSurface->h;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textureSurface);

    SDL_RenderCopyF(renderer, texture, NULL, &dest);

    SDL_DestroyTexture(texture);

    SDL_FreeSurface(textureSurface);


}

void SDLGraphics::drawText(const Text text, const float x, const float y, const Viewport viewport) const {

    SDL_Rect rectViewport;
    rectViewport.x = viewport.x;
    rectViewport.y = viewport.y;
    rectViewport.w = viewport.width;
    rectViewport.h = viewport.height;

    SDL_RenderSetViewport(renderer, &rectViewport);

    drawText(text, x, y);

    SDL_RenderSetViewport(renderer, NULL);

}

void SDLGraphics::fillRect(const float x, const float y, const float width, const float height, const Color color) const {

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_RenderFillRectF(renderer, &rect);

}

void SDLGraphics::fillRect(const float x, const float y, const float width, const float height, const Color color, const Viewport viewport) const {


    SDL_Rect rectViewport;
    rectViewport.x = viewport.x;
    rectViewport.y = viewport.y;
    rectViewport.w = viewport.width;
    rectViewport.h = viewport.height;

    SDL_RenderSetViewport(renderer, &rectViewport);

    fillRect(x, y, width, height, color);

    SDL_RenderSetViewport(renderer, NULL);

}

Image* SDLGraphics::getImage(const std::string filename) {

    if (imageNames->find(filename) == imageNames->end()) {
        loadImage(filename);
    }

    return imageNames->at(filename);

}

SDLGraphics* SDLGraphics::getGraphics(int fps, int width, int height) {
	SDLGraphics* graphics = new SDLGraphics(fps, width, height);
	graphics->initialize();
	return graphics;
}

void SDLGraphics::onClose() const {
    for (const auto& img : *images) {
        SDL_DestroyTexture(img.second);
    }
    delete images;

    for (const auto& font : *fonts) {
        TTF_CloseFont(font.second);
    }
    delete fonts;

    // Destroy renderer
    SDL_DestroyRenderer(renderer);
    
    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystem
    TTF_Quit();
    IMG_Quit();
    SDL_VideoQuit();
}