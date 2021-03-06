#include "EngineData.h"

#include "Mesh.h"
#include "GameObject.h"
#include "Camera.h"
#include "Terrain.h"
#include "PlainGameObject.h"
#include "Light.h"
#include "Skybox.h"

double EngineData::currentTime;
double EngineData::pastTime;
double EngineData::deltaTime;
double EngineData::startTime;

int EngineData::windowHeight;
int EngineData::windowWidth;

std::map<std::string,int> EngineData::keyMap;
std::vector<Mesh*> EngineData::drawMeshes;
std::vector<GameObject*> EngineData::gameObjects;
Camera* EngineData::activeCamera;

glm::vec2 EngineData::mousePosCurrent;
glm::vec2 EngineData::mousePosPast;
glm::vec2 EngineData::mouseDelta;
Light* EngineData::activeLight;

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

	EngineData::activeCamera = new Camera();
	EngineData::gameObjects.push_back(new PlainGameObject());
	EngineData::gameObjects.push_back(new PlainGameObject());

	EngineData::gameObjects[1]->transform.moveSide(10.0f);
	EngineData::gameObjects.push_back(new Skybox("data/sky"));

	EngineData::gameObjects.push_back(new Terrain());

	EngineData::activeLight = new Light();
	EngineData::activeLight->transform.moveUp(10.0f);

	EngineData::readSettings();
}

void EngineData::updateTime() {
	pastTime = currentTime;
	currentTime = glfwGetTime();
	deltaTime = currentTime - pastTime;
}

//Called every frame
void EngineData::update(double deltaT) {
	//Update mouse position and delta
	int x, y;
	glfwGetMousePos(&x,&y);
	EngineData::setMousePos(x,y);
}

//Will: Read in settings from file 
//Does: Not
void EngineData::readSettings() {
	
	windowHeight = 600;
	windowWidth = 400;

	keyMap["forward"] = GLFW_KEY_UP;
	keyMap["back"] = GLFW_KEY_DOWN;
	keyMap["left"] = GLFW_KEY_LEFT;
	keyMap["right"] = GLFW_KEY_RIGHT;
}

void EngineData::terminate() {
	delete EngineData::activeCamera;
}

Camera* EngineData::getActiveCamera() {
	return EngineData::activeCamera;
}

void EngineData::addMesh(Mesh* meshToAdd) {
	EngineData::drawMeshes.push_back(meshToAdd);
}
std::vector<Mesh*>* EngineData::getMeshesToDraw(){
	return &EngineData::drawMeshes;
}
void EngineData::removeMesh (Mesh* meshToRemove) {
	EngineData::drawMeshes.erase(
		std::find(EngineData::drawMeshes.begin(),
		EngineData::drawMeshes.end(), meshToRemove));
}

void EngineData::addGameObject(GameObject* objectToAdd) {
	EngineData::gameObjects.push_back(objectToAdd);
}
std::vector<GameObject*>* EngineData::getGameObjects(){
	return &EngineData::gameObjects;
}
void EngineData::removeGameObject (GameObject* objectToRemove) {
	EngineData::gameObjects.erase(
		std::find(EngineData::gameObjects.begin(),
		EngineData::gameObjects.end(), objectToRemove));
}

glm::vec2 EngineData::getMousePos(){
	return EngineData::mousePosCurrent;
}
glm::vec2 EngineData::getMouseDelta(){
	return EngineData::mouseDelta;
}