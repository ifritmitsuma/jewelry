#include "ScoreManager.h"
#include <layers\graphics\GraphicsManager.h>
#include "media/Text.h"
#include <iostream>

int ScoreManager::score = 0;

int ScoreManager::getScore() {
	return score;
}

void ScoreManager::addScore(unsigned int score) {
	ScoreManager::score += score;
}

void ScoreManager::drawScore() {
	Viewport scoreViewport = layers::GraphicsManager::getViewport(graphics::ViewportType::SCORE);

	media::Text text = { "Score: " + std::to_string(score), "Blader" };

	//layers::GraphicsManager::drawText(text, 0, 0, scoreViewport);

	std::cout << text.text << std::endl;
}