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

	static std::map<std::string,int> keyMap;
	static std::vector<Mesh*> drawMeshes;

	static Camera* activeCamera;

	static void readSettings();

protected:
	static void initializeData();
	static void updateTime();

	static void terminate();
	//Getters and Setters 
public:
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
};

