#include "board/BoardManager.h"
#include "board/Board.h"
#include "layers/graphics/GraphicsManager.h"
#include "layers/graphics/Viewport.h"
#include "layers/graphics/ViewportType.h"

using namespace board;

Jewel BoardManager::hover = { -1, -1, -1 };
JewelPair BoardManager::exchangingPair = { { -1, -1, -1 }, { -1, -1, -1 } };

bool BoardManager::locked = false;

Board* BoardManager::board = new Board(SIZE);

int** BoardManager::getBoard() {
	return board->getBoard();
}

bool BoardManager::sweep() {

    int count[5] = { 0, 0, 0, 0, 0 };
    bool clean = true;

    for (int i = SIZE; i < SIZE * 2; ++i) {
        
        for (int j = 0; j < SIZE; ++j) {
            int color = getBoard()[i][j];
            if (count[color - 1] == 0) {
                for (int w = 0; w < 5; ++w)
                    count[w] = 0;
            }
            count[color - 1]++;
            if (count[color - 1] == 3) {
                it = getBoard()[col].erase(it);
                it = getBoard()[col].erase(it);
                it = getBoard()[col].erase(it);
                board->generate(col, 3);
                clean = false;
            }
            if (count[color - 1] > 3) {
                it = getBoard()[col].erase(it);
                board->generate(col);
                clean = false;
            }
            it++;
        }
    }

    return clean;

}

void BoardManager::update() {

    if (BoardManager::locked) {
        if (exchangingPair.second.color != -1) {

            int tempJewel = getBoard()[exchangingPair.first.line + SIZE][exchangingPair.first.column];

            board->setJewel(exchangingPair.first.line + SIZE, exchangingPair.first.column, getBoard()[exchangingPair.second.line + SIZE][exchangingPair.second.column]);
            board->setJewel(exchangingPair.second.line + SIZE, exchangingPair.second.column, tempJewel);

            /* must change to check */
            if (!BoardManager::sweep()) {
                int tempJewel = getBoard()[exchangingPair.first.line + SIZE][exchangingPair.first.column];

                board->setJewel(exchangingPair.first.line + SIZE, exchangingPair.first.column, getBoard()[exchangingPair.second.line + SIZE][exchangingPair.second.column]);
                board->setJewel(exchangingPair.second.line + SIZE, exchangingPair.second.column, tempJewel);
            }

            exchangingPair = { { -1, -1, -1 }, { -1, -1, -1 } };

            BoardManager::locked = false;

        }
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

            
            if (hover.line == boardI && hover.column == j) {
                // Hovering jewel
                x = 5 + (j * (glow->getWidth()));
                y = 5 + (boardI * (glow->getHeight()));
                layers::GraphicsManager::drawImage(glow, x, y, boardViewport);
            }

            int color = getBoard()[i][j];

            const media::Image* image = layers::GraphicsManager::getImage("Color-" + std::to_string(color) + ".png");
            x = 10 + (j * (image->getWidth() + 10));
            y = 10 + (boardI * (image->getHeight() + 10));
            layers::GraphicsManager::drawImage(image, x, y, boardViewport);

            if (exchangingPair.first.line == boardI && exchangingPair.first.column == j) {
                // Selected jewel
                x = x + 20;
                y = y + 20;
                layers::GraphicsManager::drawImage(selected, x, y, boardViewport);
            }
            if (exchangingPair.second.line == boardI && exchangingPair.second.column == j) {
                // Selected jewel
                x = x + 20;
                y = y + 20;
                layers::GraphicsManager::drawImage(selected, x, y, boardViewport);
            }

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

    int color = getBoard()[i + SIZE][j];

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
            if (abs(exchangingPair.first.line - i) < 2 && abs(exchangingPair.first.column - j) < 2) {
                exchangingPair.second = { color, i, j };
                BoardManager::locked = true;
            }
            else {
                exchangingPair.second = { -1, -1, -1 };
                exchangingPair.first = { color, i, j };
            }
        }
        break;
    case input::MouseInputType::LEFT_BUTTON_UP:
        if (exchangingPair.first.color != -1 && abs(exchangingPair.first.line - i) < 2 && abs(exchangingPair.first.column - j) < 2) {
            if (exchangingPair.first.line - i == 0 && exchangingPair.first.column - j == 0) {
                break;
            }
            exchangingPair.second = { color, i, j };
            BoardManager::locked = true;
        }
        break;
    default:
        break;
    }

}

void BoardManager::free() {
	delete board;
}