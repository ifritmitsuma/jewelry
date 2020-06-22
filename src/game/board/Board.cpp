#include "game/board/Board.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

using namespace board;

Board::Board(int size) {

	srand((unsigned int) time(NULL));

	/*board = new int*[size];

	for (int i = 0; i < size * 2; ++i) {
		board[i] = new int[size];
		for (int j = 0; j < size; ++j) {
			board[i][j] = rand() % 5 + 1;
		}
	}*/

	board = new Matrix<int>(size * 2, size);

	for (int i = 0; i < size * 2; ++i) {
		for (int j = 0; j < size; ++j) {
			board->put(i, j, rand() % 5 + 1);
		}
	}

}

Matrix<int>* Board::getBoard() const {

	return board;

}

int Board::getJewel(const int line, const int column) const {

	return board->get(line, column);

}

void Board::setJewel(const int line, const int column, const int color) {
	
	board->put(line, column, color);

}