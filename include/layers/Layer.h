#pragma once

namespace layers {

	class Layer {

	protected:

		virtual void initialize() = 0;

		virtual void onClose() const = 0;

	};

}