#pragma once

//OpenGL + GLFW
#include <GL/glew.h> //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Standard Library
#include <vector>
#include <cstddef>	//offsetof
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

//In-Project
class GameObject;
class ShaderProgram;
class Transform;
#include "vertex.h"

//Mesh is a component of a GameObject
/*
	The Mesh interface contains all methods needed to draw a series of vertices
	to the screen. 
	Meshes register themselves with EngineData so that they may be rendered.
	A Mesh requires a GameObject to exist.
*/
//Note: plans are in place to make this more modular (i.e. mesh can have a normal or a diffuse or both).
//For now, for the sake of speed, meshes have diffuse and normalmaps
class Mesh
{
public:
	Mesh(void);
	Mesh(GameObject* owner);
	Mesh(GameObject* owner, std::string objFile, std::string diffuseMap, std::string normalMap);

	~Mesh(void);

	void draw();
	//Derivatives of Mesh should declare the gameObject that is using them and the shader they are using as friends
	friend class ShaderProgram;
	friend class BasicShaderProgram;
	friend class NormalShaderProgram;
	friend class ColorShaderProgram;

	void reverseNormals();

protected:
	Transform* getTransform();

	GameObject* owner;
	ShaderProgram* shader;

	GLuint vertexArrayID;
	GLuint vertexBufferID;
	GLuint vertexIndexID;
	GLuint textureID;
	GLuint normalMapID;

	std::vector<vertex> vertices;
	std::vector<GLuint> vertexIndices;

	void createMesh();
	void createMesh(std::string objFile, std::string diffuseMap, std::string normalMap);
	void loadOBJ(std::string fileName);
	void createShader();
	void createBuffers();
	void createTexture(std::string filename);
	void createNormalMap(std::string filename);
	void calculateTangents();
	
};

