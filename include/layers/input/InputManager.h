#pragma once

#include "layers/LayerManager.h"
#include "layers/input/Input.h"
#include "layers/input/sdl/SDLInput.h"

namespace layers {

	class InputManager : public LayerManager {

	private:

		static const Input* input;

	public:

		static void poll();

		static void free();

	};

}