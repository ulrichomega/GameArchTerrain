#include "EngineData.h"

glm::mat4 EngineData::ProjectionMatrix;
double EngineData::currentTime;
double EngineData::pastTime;
double EngineData::deltaTime;
double EngineData::startTime;

int EngineData::windowHeight;
int EngineData::windowWidth;

EngineData::EngineData(void)
{
}


EngineData::~EngineData(void)
{
}

void EngineData::initializeData() {
	ProjectionMatrix = glm::perspective(60.0f, 16.0f/9.0f, 0.1f, 100.0f);

	//My vain attempt to have the times start as reasonable values
	startTime = glfwGetTime();
	currentTime = glfwGetTime();
	deltaTime = 0.05;
	pastTime = currentTime-deltaTime;

	windowHeight = 600;
	windowWidth = 400;
}

void EngineData::updateTime() {
	pastTime = currentTime;
	currentTime = glfwGetTime();
	deltaTime = currentTime - pastTime;
}