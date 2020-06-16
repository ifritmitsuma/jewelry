#pragma once

#include "layers/input/Input.h"

namespace layers {

	class SDLInput : public Input {

	public:

		void initialize() override;

		void onClose() const override;

		void poll() const override;

		static SDLInput* getInput();

	};

}