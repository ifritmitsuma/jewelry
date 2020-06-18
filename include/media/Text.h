#pragma once
#include <string>

namespace media {

	struct TextColor {

		int r = 0;

		int g = 0;

		int b = 0;

		int a = 1;

	};

	struct Text {
	
		const std::string text;

		const std::string font;

		const int size = 8;

		const TextColor color;

	};

}