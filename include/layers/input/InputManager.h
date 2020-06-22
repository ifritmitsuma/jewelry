#pragma once

#include "layers/LayerManager.h"
#include "layers/input/Input.h"
#include "layers/input/sdl/SDLInput.h"

namespace layers {
	
	/**
	 * Class InputManager
	 *
	 * Manages the Input Layer
	 */
	class InputManager {

	private:

		// The Input plugin
		static const Input* input;

	public:

		/**
		*	Polls the system for inputs
		*/
		static void poll();

		/**
		*	Free any resources held by this manager
		*/
		static void free();

	};

}