#pragma once

//OpenGL + GLFW
#include "glew.h" //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Standard Library
#include <iostream>
#include <string>

//In-Project
#include "GameObject.h"
#include "Mesh.h"

class heightMap :
	public Mesh
{
public:
	heightMap(void);
	~heightMap(void);
	heightMap(GameObject* owner, std::string heightMapFilename);
	
	friend class Terrain;
	friend class ColorShaderProgram;

	int xSize, ySize;
	
	void draw();
private:
	void createMesh(std::string heightMapFilename);
	
	void createVertices(std::string heightMapFilename);
	void createShader();
	void calculateColor();
};

