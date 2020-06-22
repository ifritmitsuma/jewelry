#include "layers/LayerManager.h"
#include "layers/graphics/GraphicsManager.h"
#include "layers/input/InputManager.h"
#include "layers/audio/AudioManager.h"

using namespace layers;

void LayerManager::free() {
	GraphicsManager::free();
	InputManager::free();
	AudioManager::free();
}