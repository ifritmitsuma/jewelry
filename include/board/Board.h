#pragma once
#include "other/matrix.h"

namespace board {

	class Board {

	private:

		Matrix<int>* board;

	public:

		Board(int size = 8);

		Matrix<int>* getBoard() const;

		int getJewel(const int line, const int column) const;

		void setJewel(const int line, const int column, const int color);

	};

}