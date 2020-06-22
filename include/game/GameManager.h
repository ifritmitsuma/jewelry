#pragma once

#include "layers/graphics/Viewport.h"
#include "layers/input/MouseInputType.h"
#include "game/GamePhase.h"

class GameManager {

public:

	static bool quit;

	static GamePhase phase;

	static bool levelStarted;

	static void initialize();

	static void update();

	static void free();

	static void handleMouse(const input::MouseInputType type, const int x, const int y);

	static void preparePhase(GamePhase phase);

	static void changePhase(GamePhase phase, bool pauseMusic = false);

};