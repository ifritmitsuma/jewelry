#pragma once

#include "layers/graphics/Graphics.h"
#include "sdl/SDL.h"
#include "sdl/SDL_image.h"
#include <map>

namespace layers {

	class SDLGraphics : public Graphics {

	private:

		int width, height;

		SDL_Window* window = NULL;

		SDL_Renderer* renderer = NULL;

		std::map<const Image*, SDL_Texture*>* images = new std::map<const Image*, SDL_Texture*>();
		std::map<const std::string, const Image*>* imageNames = new std::map<const std::string, const Image*>();

		void loadImage(const std::string filename);

	public:

		SDLGraphics(int width, int height) : width{ width }, height{ height } {}

		void initialize() override;

		void clear() const override;

		void render() const override;

		void drawImage(const std::string imageName, const int x, const int y) const override;

		void drawImage(const Image* image, const int x, const int y) const override;

		void drawImage(const std::string imageName, const int x, const int y, const Viewport viewport) const override;

		void drawImage(const Image* image, const int x, const int y, const Viewport viewport) const override;

		const Image* getImage(const std::string filename) override;

		static SDLGraphics* getGraphics(int width, int height);

		void onClose() const override;

	};

}