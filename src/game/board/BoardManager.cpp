#include "game/board/BoardManager.h"
#include "game/board/Board.h"
#include "layers/graphics/GraphicsManager.h"
#include "layers/graphics/Viewport.h"
#include "layers/graphics/ViewportType.h"
#include "game/board/ScoreManager.h"
#include "layers/audio/AudioManager.h"
#include "game/GamePhase.h"
#include "game/GameManager.h"
#include "layers/graphics/Button.h"
#include <time.h>

using namespace board;

ScreenPosition BoardManager::mousePosition = { -1, -1 };

Jewel BoardManager::hover = { -1, -1, -1 };
Jewel BoardManager::drag = { -1, -1, -1 };
ScreenPosition BoardManager::grabPosition = { -1, -1 };
int BoardManager::failedSwap = -100;
bool BoardManager::combo = false;

JewelPair BoardManager::exchangingPair = { { -1, -1, -1 }, { -1, -1, -1 } };

bool BoardManager::locked = false;

Board* BoardManager::board = new Board(SIZE);

std::array<float, BoardManager::SIZE> BoardManager::boardMovements = std::array<float, BoardManager::SIZE>();
std::array<int, BoardManager::SIZE> BoardManager::count = std::array<int, BoardManager::SIZE>();
std::array<int, BoardManager::SIZE> BoardManager::index = std::array<int, BoardManager::SIZE>();

bool BoardManager::moving = false;

bool BoardManager::hoverExit = false;
bool BoardManager::hoverPlayAgain = false;

int BoardManager::timeLimit = 120;

int secondsToPlay = BoardManager::timeLimit;
int startTime = 0;

int scoreToAdd = 0;

void BoardManager::initialize() {
    BoardManager::mousePosition = { -1, -1 };

    BoardManager::hover = { -1, -1, -1 };
    BoardManager::drag = { -1, -1, -1 };
    BoardManager::grabPosition = { -1, -1 };
    BoardManager::failedSwap = -100;
    BoardManager::combo = false;

    scoreToAdd = 0;
    secondsToPlay = BoardManager::timeLimit;
    startTime = (int) time(0);

    BoardManager::exchangingPair = { { -1, -1, -1 }, { -1, -1, -1 } };

    BoardManager::locked = false;

    BoardManager::board = new Board(SIZE);

    BoardManager::boardMovements = std::array<float, BoardManager::SIZE>();
    BoardManager::count = std::array<int, BoardManager::SIZE>();
    BoardManager::index = std::array<int, BoardManager::SIZE>();

    BoardManager::moving = false;

    BoardManager::hoverExit = false;
    BoardManager::hoverPlayAgain = false;

    ScoreManager::initialize();

    while (board::BoardManager::sweep(true) > 0);
}

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

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

    if (secondsToPlay > 0) {
        secondsToPlay = BoardManager::timeLimit - ((int) time(0) - startTime);
    }

    if (secondsToPlay == 0) {
        BoardManager::locked = true;
    }

    if (BoardManager::drag.color != -1 && (mousePosition.x / 80 != drag.column || mousePosition.y / 80 != drag.line)) {
        exchangingPair.first = drag;
        drag = { -1, -1, -1 };
        exchangingPair.second = { 1, mousePosition.y / 80, mousePosition.x / 80 };
    }

    if (!BoardManager::moving && exchangingPair.second.color != -1 && failedSwap == -100) {

        scoreToAdd = 0;

        BoardManager::locked = true;

        //std::cout << "EXCHANGE" << std::endl;

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
        
            failedSwap = 10;

            layers::AudioManager::play("Item2A.wav");

        } else {

            exchangingPair = { { -1, -1, -1 }, { -1, -1, -1 } };

            BoardManager::locked = false;

            layers::AudioManager::play("Menu2A.wav");

        }

        scoreToAdd += score;

        ScoreManager::addScore(score);

        //std::cout << *board->getBoard() << std::endl;

    }

}

void BoardManager::checkIfFinishedMoving() {
    
    if (moving) {

        bool stillMoving = false;

        for (int column = 0; column < SIZE; ++column) {
            if (boardMovements[column] < count[column] * 80) {
                stillMoving = true;
                boardMovements[column] *= ((float)layers::GraphicsManager::SCREEN_FPS + 1.10f) / (float)layers::GraphicsManager::SCREEN_FPS;
            }
        }

        BoardManager::moving = stillMoving;

        if (!BoardManager::moving) {

            BoardManager::locked = true;

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

            int score = 0;
            if ((score = BoardManager::sweep()) > 0) {
                BoardManager::combo = true;
                //std::cout << "COMBO!" << std::endl;
                scoreToAdd += score;
                ScoreManager::addScore(score);

                layers::AudioManager::play("Accept.mp3");
            }
            else {
                BoardManager::combo = false;
                BoardManager::moving = false;
                BoardManager::locked = false;
            }

            drawBoard(false);

        }

    } else {
        scoreToAdd = 0;
    }

}

void BoardManager::drawBoard(bool drawBackground) {

    Viewport boardViewport = layers::GraphicsManager::getViewport(graphics::ViewportType::BOARD);

    

    media::Image* glow = layers::GraphicsManager::getImage("glow.png");
    media::Image* selected = layers::GraphicsManager::getImage("select.png");

    if (drawBackground) {

        media::Image* board_back_image = layers::GraphicsManager::getImage("board_back.png");

        for (int i = SIZE; i < SIZE * 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                int boardI = i - SIZE;

                float x = 5 + ((float) j * board_back_image->getWidth() + 5);
                float y = 5 + ((float) boardI * board_back_image->getHeight() + 5);
                layers::GraphicsManager::drawImage(board_back_image, x, y, boardViewport);

            }
        }

    }

    for (int i = 0; i < SIZE * 2; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int color = board->getJewel(i, j);

            int boardI = i - SIZE;

            float x = 0;
            float y = 0;

            if (!BoardManager::locked && hover.line == boardI && hover.column == j) {
                // Hovering jewel
                x = 5 + (j * (glow->getWidth()));
                y = 5 + (boardI * (glow->getHeight()));
                layers::GraphicsManager::drawImage(glow, x, y, boardViewport);
            }

            if (color > 0) {
                if (drag.color != -1 && drag.line == boardI && drag.column == j) {
                    continue;
                }
                media::Image* image = layers::GraphicsManager::getImage("Color-" + std::to_string(color) + ".png");
                x = (float) (10 + (j * ((float)image->getWidth() + 10)));
                // shake
                if (failedSwap != -100 && ((exchangingPair.first.color != -1 && exchangingPair.first.column == j && exchangingPair.first.line == boardI) ||
                    (exchangingPair.second.color != -1 && exchangingPair.second.column == j && exchangingPair.second.line == boardI))) {
                    x += 2.0f * ((float) failedSwap * -1);
                }
                y = (float) (10 + (boardI * (image->getHeight() + 10)) + (boardMovements[j] > 0 && index[j] >= i ? (std::min((float)boardMovements[j], (float)count[j] * 80)) : 0));
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

    if (failedSwap == 0) {
        failedSwap = -100;

        exchangingPair = { { -1, -1, -1 }, { -1, -1, -1 } };

        BoardManager::locked = false;
    }
    else if (failedSwap != -100) {
        bool negative = failedSwap < 0;
        failedSwap = abs(failedSwap) - 1;
        failedSwap *= (!negative ? -1 : 1);
    }

    // We need to draw the dragging piece last
    if (drag.color != -1) {
        media::Image* image = layers::GraphicsManager::getImage("Color-" + std::to_string(drag.color) + ".png");
        float x = 10 + (drag.column * (image->getWidth() + 10));
        float y = 10 + (drag.line * (image->getHeight() + 10));

        int mouseDiffX = mousePosition.x - grabPosition.x;
        int mouseDiffY = mousePosition.y - grabPosition.y;
        bool vertical = mouseDiffX > 0 ? mouseDiffX < mouseDiffY : mouseDiffX > mouseDiffY;

        x += (!vertical ? mouseDiffX : 0);
        y += (vertical ? mouseDiffY : 0);
        layers::GraphicsManager::drawImage(image, (float)x, (float)y, boardViewport);
    }

    if (drawBackground) {
        media::Image* board_border_image = layers::GraphicsManager::getImage("board_border.png");
        layers::GraphicsManager::drawImage(board_border_image, 0, 0, boardViewport);
    }

    if (secondsToPlay == 0) {
        Color color = { 255, 255, 255, 127 };

         layers::GraphicsManager::fillRect(0, 0, 650, 650, color, boardViewport);

         int fontSize = 72;
         media::Text text = { "GAME OVER", "Blader", fontSize };
         layers::GraphicsManager::drawText(text, (650 - text.size / 2 * text.text.size()) / 2.0f, (650 - text.size) / 2.0f, boardViewport);

         fontSize = 48;
         text.text = "Time up!";
         text.size = fontSize;
         layers::GraphicsManager::drawText(text, (650 - text.size / 2 * text.text.size()) / 2.0f, 75 + (650 - text.size) / 2.0f, boardViewport);

         fontSize = 22;
         text.text = std::string("Play Again");
         text.size = fontSize;

         graphics::Button* playAgain = new Button(1, text);
         playAgain->drawButton(225, 550, hoverPlayAgain, &boardViewport);

    }
    else {
        checkIfFinishedMoving();
    }

}

std::string getSecondsToPlay() {
    std::string secs = std::to_string(secondsToPlay % 60);
    secs.insert(secs.begin(), 2 - secs.size(), '0');
    return std::to_string(secondsToPlay / 60) + ":" + secs;
}

void BoardManager::drawSidebar() {

    Viewport viewport = layers::GraphicsManager::getViewport(graphics::ViewportType::SIDEBAR);

    Image* logo = layers::GraphicsManager::getImage("logo.png");

    logo->setWidth(200);
    logo->setHeight(75);

    layers::GraphicsManager::drawImage(logo, 0, 0, viewport);

    ScoreManager::drawScore();

    if (scoreToAdd) {
        int fontSize = 36;
        media::Text text = { std::to_string(scoreToAdd) + " points", "Blader", fontSize };

        layers::GraphicsManager::drawText(text, 0, 200, viewport);
    }

    if (combo) {
        int fontSize = 36;
        media::Text text = { "COMBO!", "Blader", fontSize };

        layers::GraphicsManager::drawText(text, 0, 300, viewport);
    }

    int fontSize = 36;
    media::Text text = { getSecondsToPlay(), "Blader", fontSize };

    layers::GraphicsManager::drawText(text, 0, 400, viewport);

    text.text = "Quit";

    graphics::Button* quit = new Button(1, text);
    quit->drawButton(0, 650 - 60, hoverExit, &viewport);

}

void BoardManager::handleMouse(const input::MouseInputType type, const int x, const int y, const graphics::ViewportType vType) {

    int j, i, color, diffI, diffJ;

    if (vType == ViewportType::BOARD) {

        if (x < 11 || x > 639 || y < 11 || y > 639) {
            // Not considering border
            return;
        }

        j = x / 80;
        i = y / 80;

        color = board->getJewel(i + SIZE, j);

        if (color < 1) {
            return;
        }

        diffI = -1;
        diffJ = -1;
    }

    switch (vType)
    {
    case ViewportType::BOARD:

        mousePosition = { x, y };

        if (BoardManager::locked && secondsToPlay > 0) {
            return;
        }

        if (drag.color != -1) {
            diffI = abs(drag.line - i);
            diffJ = abs(drag.column - j);
        }

        if (exchangingPair.first.color != -1) {
            diffI = abs(exchangingPair.first.line - i);
            diffJ = abs(exchangingPair.first.column - j);
        }

        switch (type) {
        case input::MouseInputType::HOVER:
            if (secondsToPlay > 0) {
                hover = { color, i, j };
            }
            else {
                if (x >= 225 && x <= 425 &&
                    y >= 550 && y <= 610) {
                    hoverPlayAgain = true;
                }
            }
            break;
        case input::MouseInputType::LEFT_BUTTON_DOWN:
            if (secondsToPlay > 0) {
                if (exchangingPair.first.color == -1) {
                    drag = { color, i, j };
                    grabPosition = mousePosition;
                }
                else {
                    if ((diffI == 1 && diffJ == 0) ||
                        (diffI == 0 && diffJ == 1)) {
                        exchangingPair.second = { color, i, j };
                    }
                    else {
                        exchangingPair.first = { -1, -1, -1 };
                        exchangingPair.second = { -1, -1, -1 };
                        drag = { color, i, j };
                        grabPosition = mousePosition;
                    }
                }
            }
            else {
                if (x >= 225 && x <= 425 &&
                    y >= 550 && y <= 610) {
                    hoverPlayAgain = false;
                    BoardManager::initialize();
                }
            }
            break;
        case input::MouseInputType::LEFT_BUTTON_UP:
            if (drag.color != -1) {
                if (diffI == 0 && diffJ == 0) {
                    exchangingPair.first = { color, i, j };
                }
                if ((diffI == 1 && diffJ == 0) ||
                    (diffI == 0 && diffJ == 1)) {
                    exchangingPair.second = { color, i, j };
                }
            }
            drag = { -1, -1, -1 };
            break;
        default:
            break;
        }

        break;

    case ViewportType::SIDEBAR:

        if (y < 590) {
            hoverExit = false;
            break;
        }
    
        switch (type) {
        case input::MouseInputType::HOVER:
            hoverExit = true;
            break;
        case input::MouseInputType::LEFT_BUTTON_DOWN:
            hoverExit = false;
            GameManager::changePhase(GamePhase::MAIN_MENU);
            
            break;
        default:
            break;
        }

        break;

    default:
        hoverPlayAgain = false;
        hoverExit = false;
        break;
    }
    

}

void BoardManager::free() {
	delete board;
}