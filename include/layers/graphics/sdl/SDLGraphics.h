#pragma once

#include "layers/graphics/Graphics.h"
#include "sdl/SDL.h"
#include "sdl/SDL_image.h"
#include "sdl/SDL_ttf.h"
#include <map>
#include <media\Text.h>

namespace layers {

	class Comparator {
	public:
		bool operator()(const Image& c1, const Image& c2) const {
			return c1.getFilename() < c2.getFilename();
		}
	};

	class SDLGraphics : public Graphics {

	private:

		Uint32 SCREEN_TICKS_PER_FRAME;

		int width, height;

		SDL_Window* window = NULL;

		SDL_Renderer* renderer = NULL;

		std::map<Image, SDL_Texture*, Comparator>* images = new std::map<Image, SDL_Texture*, Comparator>();
		std::map<const std::string, Image*>* imageNames = new std::map<const std::string, Image*>();

		std::map<const std::string, TTF_Font*>* fonts = new std::map<const std::string, TTF_Font*>();

		void loadImage(const std::string filename);

		void loadFont(const std::string font);

	public:

		SDLGraphics(int fps, int width, int height) : width{ width }, height{ height } {
			SCREEN_TICKS_PER_FRAME = 1000 / fps;
		}

		void initialize() override;

		void beforeRender() const override;

		void clear() const override;

		void render() const override;

		void drawImage(const std::string imageName, const float x, const float y) const override;

		void drawImage(Image* image, const float x, const float y) const override;

		void drawImage(const std::string imageName, const float x, const float y, const Viewport viewport) const override;

		void drawImage(Image* image, const float x, const float y, const Viewport viewport) const override;

		void drawText(const Text text, const float x, const float y) const override;

		void drawText(const Text text, const float x, const float y, const Viewport viewport) const override;

		void fillRect(const float x, const float y, const float width, const float height, const Color color) const override;

		void fillRect(const float x, const float y, const float width, const float height, const Color color, const Viewport viewport) const override;

		Image* getImage(const std::string filename) override;

		static SDLGraphics* getGraphics(int fps, int width, int height);

		void onClose() const override;

	};

}