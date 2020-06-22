#pragma once

#include "game/board/Board.h"
#include "game/board/Jewel.h"
#include "layers/input/MouseInputType.h"
#include <array>
#include "layers/graphics/ScreenPosition.h"
#include "layers/graphics/ViewportType.h"

namespace board {

	/**
	*	Class BoardManager
	*
	*	Manages the board and game logic
	*/
	class BoardManager {

	public:

		static const int SIZE = 8;

		static int timeLimit;
		
	private:

		static graphics::ScreenPosition mousePosition;

		static Jewel hover;

		static Jewel drag;

		static graphics::ScreenPosition grabPosition;

		static int failedSwap;

		static bool combo;

		static JewelPair exchangingPair;

		static Board* board;

		static std::array<float, BoardManager::SIZE> boardMovements;

		static std::array<int, BoardManager::SIZE> count;

		static std::array<int, BoardManager::SIZE> index;

		static bool moving;

		static bool hoverExit;
		static bool hoverPlayAgain;

		static void checkIfFinishedMoving();

	public:

		// Whether the board is locked or not
		static bool locked;

		static Matrix<int>* getBoard();

		static void initialize();

		/**
		*	Sweeps the board to calculate if there are any jewels to burst and which
		*
		*	@param instantaneous Whether or not to just persist the changes or enable animations
		*	@return The score associated with the sweep (0 score means nothing in the board changes)
		*/
		static int sweep(bool instantaneous = false);

		/**
		*	Called every frame
		*/
		static void update();

		/**
		*	Draws the board
		*
		*	@param drawBackground Whether or not to draw the board background
		*/
		static void drawBoard(bool drawBackground = true);

		/**
		*	Draws the sidebar
		*/
		static void drawSidebar();

		/**
		*	Handle mouse events
		*
		*	@param type The type of mouse event
		*	@param x The x coordinate of the cursor in the screen
		*	@param y The y coordinate of the cursor in the screen
		*	@param vType The Viewport where the cursor is
		*/
		static void handleMouse(const input::MouseInputType type, const int x, const int y, const graphics::ViewportType vType);

		/**
		*	Free any resources held by this manager
		*/
		static void free();

	};

}