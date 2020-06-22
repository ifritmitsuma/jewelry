#pragma once
#include "layers/input/MouseInputType.h"
#include "layers/graphics/ViewportType.h"

class MainMenuManager
{

private:

	static int hover;

public:

	static void update();

	static void drawMainMenu();

	static void handleMouse(const input::MouseInputType type, const int x, const int y, const graphics::ViewportType vType);

	static void free();

};

