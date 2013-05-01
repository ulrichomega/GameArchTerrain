#include "GameEngine.h"


GameEngine::GameEngine(void)
{

}


GameEngine::~GameEngine(void)
{
}


void GameEngine::run() {
	EngineData::initializeData();

	bool running = true;
	while (running) {
		updateTime();
		update();
		draw();
	}
}

void GameEngine::setup() {

}

void GameEngine::updateTime() {
	EngineData::updateTime();
}

void GameEngine::update() {

}

void GameEngine::draw() {

}