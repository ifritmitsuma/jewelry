#pragma once

#include "layers/graphics/Graphics.h"
#include "sdl/SDL.h"
#include "sdl/SDL_image.h"
#include "sdl/SDL_ttf.h"
#include <map>
#include <media\Text.h>

namespace layers {

	class SDLGraphics : public Graphics {

	private:

		int SCREEN_TICKS_PER_FRAME;

		int width, height;

		SDL_Window* window = NULL;

		SDL_Renderer* renderer = NULL;

		std::map<const Image*, SDL_Texture*>* images = new std::map<const Image*, SDL_Texture*>();
		std::map<const std::string, const Image*>* imageNames = new std::map<const std::string, const Image*>();

		std::map<const std::string, TTF_Font*>* fonts = new std::map<const std::string, TTF_Font*>();

		void loadImage(const std::string filename);

		void loadFont(const std::string font);

	public:

		SDLGraphics(int fps, int width, int height) : width{ width }, height{ height } {
			SCREEN_TICKS_PER_FRAME = 1000 / fps;
		}

		void initialize() override;

		void clear() const override;

		void render() const override;

		void drawImage(const std::string imageName, const float x, const float y) const override;

		void drawImage(const Image* image, const float x, const float y) const override;

		void drawImage(const std::string imageName, const float x, const float y, const Viewport viewport) const override;

		void drawImage(const Image* image, const float x, const float y, const Viewport viewport) const override;

		void drawText(const Text text, const int x, const int y) const override;

		void drawText(const Text text, const int x, const int y, const Viewport viewport) const override;

		const Image* getImage(const std::string filename) override;

		static SDLGraphics* getGraphics(int fps, int width, int height);

		void onClose() const override;

	};

}