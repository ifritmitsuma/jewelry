#pragma once
#include "other/matrix.h"

namespace board {

	/**
	*	Class Board
	*
	*	Represents a Jewelry Game board
	*/
	class Board {

	private:

		// The state of the board in an int matrix representation
		Matrix<int>* board;

	public:

		Board(int size = 8);

		/**
		*	Returns the board
		*
		*	@return The board matrix
		*/
		Matrix<int>* getBoard() const;

		/**
		*	Gets the jewel placed in the line and column
		*
		*	@param line The line
		*	@param column The column
		*/
		int getJewel(const int line, const int column) const;

		/**
		*	Places a jewel with color in the line and column
		*
		*	@param line The line
		*	@param column The column
		*	@param color The color
		*/
		void setJewel(const int line, const int column, const int color);

	};

}