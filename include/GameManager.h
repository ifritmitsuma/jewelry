#pragma once

#include "layers/graphics/Viewport.h"
#include "layers/input/MouseInputType.h"
#include <GamePhase.h>

class GameManager {

public:

	static bool quit;

	static GamePhase phase;

	static void initialize();

	static void update();

	static void free();

	static void handleMouse(const input::MouseInputType type, const int x, const int y);

};