#pragma once

namespace board {

	struct Jewel {

		int color;
		int line;
		int column;

	};

	struct JewelPair {

		Jewel first;
		Jewel second;

	};

}