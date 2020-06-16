#include "layers/input/InputManager.h"

using namespace layers;

const Input* InputManager::input = SDLInput::getInput();

void InputManager::poll() {

	input->poll();

}

void InputManager::free() {
	input->onClose();
}