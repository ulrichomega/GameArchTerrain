#pragma once

#include <iostream>
#include "GameEngine.h"

int main () {
	std::cout << "HELLO WORLD!" << std::endl;

	GameEngine engine;
	engine.setup();
	engine.run();

	return 1;
}

