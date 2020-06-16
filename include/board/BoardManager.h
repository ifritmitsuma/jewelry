#pragma once

#include "board/Board.h"
#include "board/Jewel.h"
#include "layers/input/MouseInputType.h"

namespace board {

	class BoardManager {
		
	private:

		static Jewel hover;

		static JewelPair exchangingPair;

		static Board* board;

	public:

		static bool locked;

		static const int SIZE = 8;

		static int** getBoard();

		static bool sweep();

		static void update();

		static void drawBoard();

		static void handleMouse(const input::MouseInputType type, const int x, const int y);

		static void free();

	};

}