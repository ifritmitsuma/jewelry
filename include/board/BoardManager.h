#pragma once

#include "board/Board.h"
#include "board/Jewel.h"
#include "layers/input/MouseInputType.h"
#include <array>

namespace board {

	class BoardManager {

	public:

		static const int SIZE = 8;
		
	private:

		static Jewel hover;

		static JewelPair exchangingPair;

		static Board* board;

		static std::array<int, BoardManager::SIZE> boardMovements;

		static std::array<int, BoardManager::SIZE> count;

		static std::array<int, BoardManager::SIZE> index;

		static bool moving;

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