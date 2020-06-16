#include "board/Board.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

using namespace board;

Board::Board(int size) {

	srand((unsigned int) time(NULL));

	board = new int*[size];

	for (int i = 0; i < size * 2; ++i) {
		board[i] = new int[size];
		for (int j = 0; j < size; ++j) {
			board[i][j] = rand() % 5 + 1;
		}
	}

}

int** Board::getBoard() const {

	return board;

}

void Board::setJewel(const int line, const int column, const int color) {
	
	board[line][column] = color;

}