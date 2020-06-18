#include "board/BoardManager.h"
#include "board/Board.h"
#include "layers/graphics/GraphicsManager.h"
#include "layers/graphics/Viewport.h"
#include "layers/graphics/ViewportType.h"
#include <ScoreManager.h>

using namespace board;

Jewel BoardManager::hover = { -1, -1, -1 };
JewelPair BoardManager::exchangingPair = { { -1, -1, -1 }, { -1, -1, -1 } };

bool BoardManager::locked = false;

Board* BoardManager::board = new Board(SIZE);

std::array<int, BoardManager::SIZE> BoardManager::boardMovements = std::array<int, BoardManager::SIZE>();
std::array<int, BoardManager::SIZE> BoardManager::count = std::array<int, BoardManager::SIZE>();
std::array<int, BoardManager::SIZE> BoardManager::index = std::array<int, BoardManager::SIZE>();

bool BoardManager::moving = false;

Matrix<int>* BoardManager::getBoard() {
	return board->getBoard();
}

void generateNew(std::vector<int> row, int count) {
    std::vector<int>::iterator it = row.begin();
    while (count > 0) {
        it = row.insert(it, rand() % 5 + 1);
        --count;
    }
}

int BoardManager::sweep(bool instantaneous) {

    int score = 0;

    for (int line = SIZE; line < SIZE * 2; ++line) {

        Matrix<int> row = board->getBoard()->getRow(line);

        int p1 = 0, p2 = 0;
        int previousColor = 0;

        while (p2 < SIZE + 1) {
            int value = 0;
            if (p2 < SIZE) {
                value = row.get(0, p2);
            }
            if (value > 5) {
                value /= 10;
            }
            if (value != previousColor) {
                if (p2 - p1 > 2) {
                    while (p1 < p2) {
                        row.put(0, p1++, previousColor * 10);
                    }
                }
                p1 = p2;
            }
            previousColor = value;
            ++p2;
        }

        for (int col = 0; col < SIZE; ++col) {
            board->setJewel(line, col, row.get(0, col));
        }

    }

    board->getBoard()->transpose();

    for (int line = 0; line < SIZE; ++line) {

        Matrix<int> row = board->getBoard()->getRow(line);

        int p1 = SIZE, p2 = SIZE;
        int previousColor = 0;

        while (p2 < SIZE * 2 + 1) {
            int value = 0;
            if (p2 < SIZE * 2) {
                value = row.get(0, p2);
            }
            if (value > 5) {
                value /= 10;
            }
            if (value != previousColor) {
                if (p2 - p1 > 2) {
                    while (p1 < p2) {
                        row.put(0, p1++, previousColor * 10);
                    }
                }
                p1 = p2;
            }
            previousColor = value;
            ++p2;
        }

        for (int col = SIZE; col < SIZE * 2; ++col) {
            board->setJewel(line, col, row.get(0, col));
        }

    }

    board->getBoard()->operator%(10); // Settings pieces to remove to zero

    //std::cout << *board->getBoard() << std::endl;

    for (int line = 0; line < SIZE; ++line) {

        std::vector<int> row = board->getBoard()->getRowAsVec(line);

        std::vector<int>::iterator it = row.begin();

        int count = 0;
        for (it = row.begin(); it != row.end(); ++it) {
            if (*it == 0) {
                if (it - row.begin() > SIZE - 1) {
                    score += 10;
                }
                if (instantaneous) {
                    it = row.erase(it);
                    --it;
                }
                else {
                    BoardManager::moving = true;
                    BoardManager::boardMovements[line] = 1;
                    BoardManager::count[line]++;
                    BoardManager::index[line] = it - row.begin();
                }
                ++count;
            }
        }

        if (instantaneous) {
            it = row.begin();
            while (count > 0) {
                it = row.insert(it, rand() % 5 + 1);
                --count;
            }
        }

        board->getBoard()->setRow(line, row);

    }

    board->getBoard()->transpose();

    return score;

}

void BoardManager::update() {

    if (BoardManager::moving) {
            
        BoardManager::moving = boardMovements != std::array<int, SIZE>();
            
        if (!BoardManager::moving) {

            BoardManager::index = std::array<int, BoardManager::SIZE>();

            board->getBoard()->transpose();
            for (int column = 0; column < SIZE; ++column) {


                std::vector<int> row = board->getBoard()->getRowAsVec(column);
                std::vector<int>::iterator it = row.begin();

                int count = 0;
                for (it = row.begin(); it != row.end(); ++it) {
                    if (*it == 0) {
                        it = row.erase(it);
                        --it;
                        ++count;
                    }
                }
                
                it = row.begin();
                while (BoardManager::count[column] > 0) {
                    it = row.insert(row.begin(), rand() % 5 + 1);
                    BoardManager::count[column]--;
                }
                board->getBoard()->setRow(column, row);

            }
            board->getBoard()->transpose();
            

            int combo = 0;
            if ((combo = BoardManager::sweep()) > 0) {
                std::cout << "COMBO!" << std::endl;
                ScoreManager::addScore(combo);
            }
            else {
                BoardManager::locked = false;
            }
            
        }

    } else if (exchangingPair.second.color != -1) {

        BoardManager::locked = true;

        std::cout << "EXCHANGE" << std::endl;

        //std::cout << *board->getBoard() << std::endl;

        int tempJewel = board->getJewel(exchangingPair.first.line + SIZE, exchangingPair.first.column);

        board->setJewel(exchangingPair.first.line + SIZE, exchangingPair.first.column, board->getJewel(exchangingPair.second.line + SIZE, exchangingPair.second.column));
        board->setJewel(exchangingPair.second.line + SIZE, exchangingPair.second.column, tempJewel);

        /* must change to check */
        int score = 0;
        if ((score = BoardManager::sweep()) == 0) {
            int tempJewel = board->getJewel(exchangingPair.first.line + SIZE, exchangingPair.first.column);

            board->setJewel(exchangingPair.first.line + SIZE, exchangingPair.first.column, board->getJewel(exchangingPair.second.line + SIZE, exchangingPair.second.column));
            board->setJewel(exchangingPair.second.line + SIZE, exchangingPair.second.column, tempJewel);
        }

        ScoreManager::addScore(score);

        ScoreManager::drawScore();

        //std::cout << *board->getBoard() << std::endl;

        exchangingPair = { { -1, -1, -1 }, { -1, -1, -1 } };


    }

}

void BoardManager::drawBoard() {

    Viewport boardViewport = layers::GraphicsManager::getViewport(graphics::ViewportType::BOARD);

    const media::Image* board_border_image = layers::GraphicsManager::getImage("board_border.png");

    const media::Image* board_back_image = layers::GraphicsManager::getImage("board_back.png");

    const media::Image* glow = layers::GraphicsManager::getImage("glow.png");
    const media::Image* selected = layers::GraphicsManager::getImage("select.png");

    for (int i = SIZE; i < SIZE * 2; ++i) {
        for (int j = 0; j < SIZE; ++j) {

            int boardI = i - SIZE;

            int x = 5 + (j * board_back_image->getWidth() + 5);
            int y = 5 + (boardI * board_back_image->getHeight() + 5);
            layers::GraphicsManager::drawImage(board_back_image, x, y, boardViewport);

            if (!BoardManager::locked && hover.line == boardI && hover.column == j) {
                // Hovering jewel
                x = 5 + (j * (glow->getWidth()));
                y = 5 + (boardI * (glow->getHeight()));
                layers::GraphicsManager::drawImage(glow, x, y, boardViewport);
            }

        }
    }

    for (int i = 0; i < SIZE * 2; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int color = board->getJewel(i, j);

            int boardI = i - SIZE;

            int x = 0;
            int y = 0;

            if (color > 0) {
                const media::Image* image = layers::GraphicsManager::getImage("Color-" + std::to_string(color) + ".png");
                int under = 10 + ((boardI + 1) * (image->getHeight() + 10));
                x = 10 + (j * (image->getWidth() + 10));
                y = 10 + (boardI * (image->getHeight() + 10)) + (boardMovements[j] > 0 && index[j] >= i ? boardMovements[j] : 0);
                if (under * count[j] <= y) {
                    boardMovements[j] = 0;
                }
                layers::GraphicsManager::drawImage(image, x, y, boardViewport);
            }

            if (!BoardManager::locked && exchangingPair.first.line == boardI && exchangingPair.first.column == j) {
                // Selected jewel
                x = x + 20;
                y = y + 20;
                layers::GraphicsManager::drawImage(selected, x, y, boardViewport);
            }
            if (!BoardManager::locked && exchangingPair.second.line == boardI && exchangingPair.second.column == j) {
                // Selected jewel
                x = x + 20;
                y = y + 20;
                layers::GraphicsManager::drawImage(selected, x, y, boardViewport);
            }
        }
    }

    for (int column = 0; column < SIZE; ++column) {
        if (boardMovements[column] > 0) {
            boardMovements[column] += 3;
        }
    }

    layers::GraphicsManager::drawImage(board_border_image, 0, 0, boardViewport);
}

void BoardManager::handleMouse(const input::MouseInputType type, const int x, const int y) {
    
    if (x < 11 || x > 639 || y < 11 || y > 639) {
        // Not considering border
        return;
    }

    int j = x / 80;
    int i = y / 80;

    int color = board->getJewel(i + SIZE, j);

    int diffI = -1;
    int diffJ = -1;

    if (exchangingPair.first.color != -1) {
        diffI = abs(exchangingPair.first.line - i);
        diffJ = abs(exchangingPair.first.column - j);
    }

    switch (type) {
    case input::MouseInputType::HOVER:
        hover = { color, i, j };
        break;
    case input::MouseInputType::LEFT_BUTTON_DOWN:
        if (exchangingPair.first.color == -1) {
            exchangingPair.second = { -1, -1, -1 };
            exchangingPair.first = { color, i, j };
        }
        else {
            if ((diffI == 1 && diffJ == 0) ||
                (diffI == 0 && diffJ == 1)) {
                exchangingPair.second = { color, i, j };
            }
            else {
                exchangingPair.second = { -1, -1, -1 };
                exchangingPair.first = { color, i, j };
            }
        }
        break;
    case input::MouseInputType::LEFT_BUTTON_UP:
        if (exchangingPair.first.color != -1) {
            if ((diffI == 1 && diffJ == 0) ||
                (diffI == 0 && diffJ == 1)) {
                exchangingPair.second = { color, i, j };
            }
        }
        break;
    default:
        break;
    }

}

void BoardManager::free() {
	delete board;
}