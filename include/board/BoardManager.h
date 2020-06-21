#pragma once

#include "board/Board.h"
#include "board/Jewel.h"
#include "layers/input/MouseInputType.h"
#include <array>
#include <layers\graphics\ScreenPosition.h>

namespace board {

	class BoardManager {

	public:

		static const int SIZE = 8;
		
	private:

		static graphics::ScreenPosition mousePosition;

		static Jewel hover;

		static Jewel drag;

		static graphics::ScreenPosition grabPosition;

		static int failedSwap;

		static JewelPair exchangingPair;

		static Board* board;

		static std::array<float, BoardManager::SIZE> boardMovements;

		static std::array<int, BoardManager::SIZE> count;

		static std::array<int, BoardManager::SIZE> index;

		static bool moving;

		static void checkIfFinishedMoving();

	public:

		static bool locked;

		static Matrix<int>* getBoard();

		//static int sweep(bool instantaneous = true);

		static int sweep(bool instantaneous = false);

		static void update();

		static void drawBoard();

		static void handleMouse(const input::MouseInputType type, const int x, const int y);

		static void free();

	};

}