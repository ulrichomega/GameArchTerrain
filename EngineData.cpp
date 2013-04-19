#include "EngineData.h"

glm::mat4 EngineData::ProjectionMatrix;
double EngineData::currentTime;
double EngineData::pastTime;
double EngineData::deltaTime;

EngineData::EngineData(void)
{
}


EngineData::~EngineData(void)
{
}

void EngineData::initializeData() {
	ProjectionMatrix = glm::perspective(60.0f, 16.0f/9.0f, 0.1f, 100.0f);
}

void EngineData::updateTime() {
	pastTime = currentTime;
	currentTime = glfwGetTime();
	deltaTime = currentTime - pastTime;
}