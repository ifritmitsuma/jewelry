#pragma once
#include <string>
#include "layers/graphics/Color.h"

namespace media {

	struct Text {
	
		std::string text;

		std::string font;

		int size = 12;

		graphics::Color color = { 0, 0, 0, 255 };

	};

}