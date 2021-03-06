#pragma once

//OpenGL + GLFW
#include "glew.h" //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Standard Library
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

//In-Project
//class EngineData;
class Mesh;
class Camera;
class GameObject;
class Light;

class EngineData
{
public:
	friend class GameEngine;
	EngineData(void);
	~EngineData(void);
private:
	//Window information, supports one (1) window for now
	static int windowHeight;
	static int windowWidth;
	static int windowHandle;

	//Time data
	static double currentTime;
	static double pastTime;
	static double deltaTime;
	static double startTime;

	//Game Objects and such
	static std::vector<Mesh*> drawMeshes;
	static std::vector<GameObject*> gameObjects;
	static Light* activeLight; //Yes, only one light for now
	
	//Input
	static std::map<std::string,int> keyMap;
	static glm::vec2 mousePosCurrent;
	static glm::vec2 mousePosPast;
	static glm::vec2 mouseDelta;

	//Currently active objects
	static Camera* activeCamera;

	static void readSettings();

protected:
	static void initializeData();
	static void updateTime();

	static void terminate();
	//Getters and Setters 
public:
	static void update(double deltaT);

	//Note: Set does not resize window and will lead to shenanigans if called
	static void setwindowHeight(int amount) {
		windowHeight = amount;
	}
	static int getWindowHeight () {
		return windowHeight;
	}

	//Note: Set does not resize window and will lead to shenanigans if called
	static void setwindowWidth(int amount) {
		windowWidth = amount;
	}
	static int getWindowWidth () {
		return windowWidth;
	}

	//Note: Set does not affect window and will lead to shenanigans if called
	static void setwindowHandle(int amount) {
		windowHandle = amount;
	}
	static int getWindowHandle () {
		return windowHandle;
	}

	static double getCurrentTime () {
		return currentTime;
	}
	static double getPastTime () {
		return pastTime;
	}
	static double getDeltaTime () {
		return deltaTime;
	}
	static double getStartTime () {
		return startTime;
	}

	static Camera* getActiveCamera();

	//Returns the key that is bound to the given action
	/*Actions include:
		Forward
		Back
		Left
		Right
		Quit	
	*/
	static int getActionKey(std::string keyToGet) {
		if (EngineData::keyMap.find(keyToGet) != EngineData::keyMap.end()) {
			//std::cout << "Giving out key: " << EngineData::keyMap[keyToGet] << std::endl;
			return EngineData::keyMap[keyToGet];
		}
		else {
			std::cout << "Could not find key: " << keyToGet << std::endl;
			throw "Could not find key";
		}
	}
	
	static void addMesh(Mesh* meshToAdd);
	static std::vector<Mesh*>* getMeshesToDraw();
	static void removeMesh (Mesh* meshToRemove);

	static void addGameObject(GameObject* objectToAdd);
	static std::vector<GameObject*>* getGameObjects();
	static void removeGameObject (GameObject* objectToRemove);

	static Light* getActiveLight() {
		return EngineData::activeLight;
	}

	static glm::vec2 getMousePos();
	static glm::vec2 getMouseDelta();
	static void setMousePos(int x, int y) {
		EngineData::mousePosPast = EngineData::mousePosCurrent;
		EngineData::mousePosCurrent = glm::vec2(x,y);
		EngineData::mouseDelta = EngineData::mousePosCurrent - EngineData::mousePosPast;
	}
};

