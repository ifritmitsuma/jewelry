#include "layers/LayerManager.h"
#include "layers/graphics/GraphicsManager.h"
#include "layers/input/InputManager.h"

using namespace layers;

void LayerManager::free() {
	GraphicsManager::free();
	InputManager::free();
}