#include "layers/graphics/GraphicsManager.h"
#include "layers/graphics/sdl/SDLGraphics.h"

using namespace layers;

const int GraphicsManager::SCREEN_WIDTH = 1024;
const int GraphicsManager::SCREEN_HEIGHT = 768;

Graphics* GraphicsManager::graphics = SDLGraphics::getGraphics(GraphicsManager::SCREEN_WIDTH, GraphicsManager::SCREEN_HEIGHT);

std::map<const ViewportType, const Viewport>* GraphicsManager::viewports = new std::map<const ViewportType, const Viewport>();

const bool GraphicsManager::isClosed() {
	return graphics->isClosed();
}

void GraphicsManager::drawImage(const std::string imageName, const int x, const int y) {
	graphics->drawImage(imageName, x, y);
}

void GraphicsManager::drawImage(const Image* image, const int x, const int y) {
	graphics->drawImage(image, x, y);
}

void GraphicsManager::drawImage(const std::string imageName, const int x, const int y, const Viewport viewport) {
	graphics->drawImage(imageName, x, y, viewport);
}

void GraphicsManager::drawImage(const Image* image, const int x, const int y, const Viewport viewport) {
	graphics->drawImage(image, x, y, viewport);
}

void GraphicsManager::clear() {
	graphics->clear();
}

void GraphicsManager::render() {
	graphics->render();
}

const media::Image* GraphicsManager::getImage(const std::string filename) {
	return graphics->getImage(filename);
}

void GraphicsManager::createNewViewport(const ViewportType vType, const int x, const int y, const int width, const int height) {
	viewports->insert(std::pair<const ViewportType, const Viewport>(vType, { x, y, width, height, vType }));
}

const Viewport GraphicsManager::getViewport(const ViewportType vType) {
	return viewports->at(vType);
}

const Viewport GraphicsManager::getViewportForCoordinate(int* x, int* y) {
	int realX = *x;
	int realY = *y;
	for (std::pair<const ViewportType, const Viewport> viewportPair : *viewports) {
		Viewport viewport = viewportPair.second;
		if (realX >= viewport.x && realX <= viewport.x + viewport.width &&
			realY >= viewport.y && realY <= viewport.y + viewport.height) {
			*x = *x - viewport.x;
			*y = *y - viewport.y;
			return viewport;
		}
	}
	Viewport ret = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	return ret;
}

void GraphicsManager::free() {
	graphics->onClose();
}