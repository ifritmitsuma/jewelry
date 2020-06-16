#pragma once

#include "layers/LayerManager.h"
#include "layers/graphics/Graphics.h"
#include "media/Image.h"
#include "layers/graphics/Viewport.h"
#include "layers/graphics/ViewportType.h"
#include <map>

using namespace graphics;

namespace layers {

	/**
	 * Class GraphicsManager
	 *
	 * Manages the Graphics Layer
	 */
	class GraphicsManager : public LayerManager {

	private:

		static const int SCREEN_WIDTH;
		static const int SCREEN_HEIGHT;

		static  Graphics* graphics;

		static std::map<const ViewportType, const Viewport>* viewports;

	public:

		/**
		*	Indicates if the Graphics Window has been closed
		*
		*	@return true if window has been closed, false otherwise
		*/
		static const bool isClosed();

		/**
		*	Draws an Image in the Graphics Window
		*
		*	@param imageName The name of the Image to draw
		*/
		static void drawImage(const std::string imageName, const int x, const int y);

		/**
		*	Draws an Image in the Graphics Window
		*
		*	@param image The Image to draw
		*/
		static void drawImage(const Image* image, const int x, const int y);

		/**
		*	Draws an Image in a viewport area of the Graphics Window
		*
		*	@param imageName The name of the Image to draw
		*/
		static void drawImage(const std::string imageName, const int x, const int y, const Viewport viewport);

		/**
		*	Draws an Image in a viewport area of the Graphics Window
		*
		*	@param image The Image to draw
		*/
		static void drawImage(const Image* image, const int x, const int y, const Viewport viewport);

		static void clear();

		static void render();

		static const Image* getImage(const std::string filename);

		static void createNewViewport(const ViewportType vType, const int x, const int y, const int width, const int height);

		static const Viewport getViewport(const ViewportType vType);

		static const Viewport getViewportForCoordinate(int* x, int* y);

		static void free();

	};

}