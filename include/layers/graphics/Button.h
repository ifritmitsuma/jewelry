#pragma once
#include "media/Text.h"
#include "layers/graphics/Viewport.h"

namespace graphics {

	class Button {

	private:

		int size = 1;

		media::Text text;

	public:

		Button(int size, media::Text text) : size{ size }, text{ text } {};

		void drawButton(const float containerX, const float containerY, const bool hover, const graphics::Viewport* viewport = nullptr) const;

	};

}