#pragma once

#include "layers/graphics/ViewportType.h"

namespace graphics {

	struct Viewport {

		int x;
		int y;
		int width;
		int height;
		ViewportType name;

	};

}