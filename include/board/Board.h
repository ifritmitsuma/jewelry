#pragma once
#include <list>

namespace board {

	class Board {

	private:

		int** board;

	public:

		Board(int size = 8);

		int** getBoard() const;

		void setJewel(const int line, const int column, const int color);

	};

}