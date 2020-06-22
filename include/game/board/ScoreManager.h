#pragma once

class ScoreManager {

private:

	static int score;

public:

	static void initialize();

	static int getScore();

	static void addScore(unsigned int score);

	static void drawScore();

};