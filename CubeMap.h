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

class CubeMap : public Mesh
{
public:
	friend class Skybox;
	friend class BasicShaderProgram;
	CubeMap(void);
	CubeMap(GameObject* owner, std::string textureNameBase);
	~CubeMap(void);
	
	void draw();

protected:
	void createVertices();
	void createMesh(std::string textureNameBase);

	/*
	Order:
		Right
		Left
		Top
		Bottom
		Back
		Front
	*/
	GLuint textureID[6];

	void createTexture(int textureIndex, std::string filename);

private:
	void createShader();

	void createRightVertices();
	void createLeftVertices();
	void createTopVertices();
	void createBottomVertices();
	void createBackVertices();
	void createFrontVertices();
};

