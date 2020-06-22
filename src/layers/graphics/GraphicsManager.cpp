#include "layers/graphics/GraphicsManager.h"
#include "layers/graphics/sdl/SDLGraphics.h"

using namespace layers;

const int GraphicsManager::SCREEN_FPS = 60;
const int GraphicsManager::SCREEN_WIDTH = 1024;
const int GraphicsManager::SCREEN_HEIGHT = 768;

Graphics* GraphicsManager::graphics = SDLGraphics::getGraphics(GraphicsManager::SCREEN_FPS, GraphicsManager::SCREEN_WIDTH, GraphicsManager::SCREEN_HEIGHT);

std::map<const ViewportType, const Viewport>* GraphicsManager::viewports = new std::map<const ViewportType, const Viewport>();

const bool GraphicsManager::isClosed() {
	return graphics->isClosed();
}

void GraphicsManager::drawImage(const std::string imageName, const float x, const float y) {
	graphics->drawImage(imageName, x, y);
}

void GraphicsManager::drawImage(Image* image, const float x, const float y) {
	graphics->drawImage(image, x, y);
}

void GraphicsManager::drawImage(const std::string imageName, const float x, const float y, const Viewport viewport) {
	graphics->drawImage(imageName, x, y, viewport);
}

void GraphicsManager::drawImage(Image* image, const float x, const float y, const Viewport viewport) {
	graphics->drawImage(image, x, y, viewport);
}

void GraphicsManager::drawText(const media::Text text, const float x, const float y) {
	graphics->drawText(text, x, y);
}

void GraphicsManager::drawText(const media::Text text, const float x, const float y, const Viewport viewport) {
	graphics->drawText(text, x, y, viewport);
}

void GraphicsManager::fillRect(const float x, const float y, const float width, const float height, const Color color) {
	graphics->fillRect(x, y, width, height, color);
}

void GraphicsManager::fillRect(const float x, const float y, const float width, const float height, const Color color, const Viewport viewport) {
	graphics->fillRect(x, y, width, height, color, viewport);
}

void GraphicsManager::beforeRender() {
	graphics->beforeRender();
}

void GraphicsManager::clear() {
	graphics->clear();
}

void GraphicsManager::render() {
	graphics->render();
}

media::Image* GraphicsManager::getImage(const std::string filename) {
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

void GraphicsManager::clearViewports() {
	viewports->clear();
}

void GraphicsManager::free() {
	graphics->onClose();
}