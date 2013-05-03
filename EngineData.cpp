#include "EngineData.h"

double EngineData::currentTime;
double EngineData::pastTime;
double EngineData::deltaTime;
double EngineData::startTime;

int EngineData::windowHeight;
int EngineData::windowWidth;

std::map<std::string,int> EngineData::keyMap;
std::vector<Mesh*> EngineData::drawMeshes;

EngineData::EngineData(void)
{
}


EngineData::~EngineData(void)
{
}

void EngineData::initializeData() {
	//My vain attempt to have the times start as reasonable values
	startTime = glfwGetTime();
	currentTime = glfwGetTime();
	deltaTime = 0.05;
	pastTime = currentTime-deltaTime;

	EngineData::readSettings();
}

void EngineData::updateTime() {
	pastTime = currentTime;
	currentTime = glfwGetTime();
	deltaTime = currentTime - pastTime;
}

//Will: Read in settings from file 
//Does: Not
void EngineData::readSettings() {
	
	windowHeight = 600;
	windowWidth = 400;

	keyMap["forward"] = 'w';
	keyMap["back"] = 's';
	keyMap["left"] = 'a';
	keyMap["right"] = 'd';
}

void EngineData::addMesh(Mesh* meshToAdd) {
	EngineData::drawMeshes.push_back(meshToAdd);
}
std::vector<Mesh*> EngineData::getMeshesToDraw(){
	return EngineData::drawMeshes;
}
void EngineData::removeMesh (Mesh* meshToRemove) {
	EngineData::drawMeshes.erase(
		std::find(EngineData::drawMeshes.begin(),
		EngineData::drawMeshes.end(), meshToRemove));
}