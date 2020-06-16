#pragma once

#include "layers/Layer.h"

namespace layers {

	class Input : public Layer {

	public:

		virtual void initialize() = 0;

		virtual void onClose() const = 0;

		virtual void poll() const = 0;

	};

}