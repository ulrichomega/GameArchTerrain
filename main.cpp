#pragma once

#include <iostream>
#include "GameEngine.h"

//Globals
GameEngine engine;

//Function prototypes
void setupGLFWCalls();
void GLFWCALL handleKeysCaller(int key, int action);
void GLFWCALL handleMouseCaller(int button, int action);
void GLFWCALL handleMousePosCaller(int x, int y);
void GLFWCALL handleMouseWheelCaller(int pos);

int main () {
	std::cout << "HELLO WORLD!" << std::endl;

	engine.setup();

	setupGLFWCalls();

	engine.run();

	return 1;
}


void setupGLFWCalls() {
	glfwSetKeyCallback( *handleKeysCaller );
	glfwSetMouseButtonCallback( *handleMouseCaller );
	glfwSetMousePosCallback( *handleMousePosCaller );
	glfwSetMouseWheelCallback( *handleMouseWheelCaller );
}

void GLFWCALL handleKeysCaller(int key, int action) {
	engine.handleKeyboard(key,action);
}
void GLFWCALL handleMouseCaller (int button, int action ) {
	engine.handleMouse(button, action);
}
void GLFWCALL handleMousePosCaller(int x, int y) {
	engine.handleMousePos(x,y);
}
void GLFWCALL handleMouseWheelCaller(int pos) {
	engine.handleMouseWheel(pos);
}