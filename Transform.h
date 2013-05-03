#pragma once

//OpenGL + GLFW
#include "glew.h" //MUST come before GLFW!
#include <GL/glfw.h>

//Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Standard Library
#include <vector>

//In-Project
//class Transform;

class Transform
{
public:
	Transform(void);
	~Transform(void);
	
	glm::mat4 transformMatrix;

	//Preserved for possible future implementation.
	//Transform* parent;
	//std::vector<Transform*> children;

	void setTransformMatrix(glm::mat4 transformMatrix);
	glm::mat4* getTransformMatrix();

	//Move transform in absolute coordinates
	void moveX(float amount);
	void moveY(float amount);
	void moveZ(float amount);
	void moveVec(glm::vec3 translation);

	//Move transform relative to current facing
	void moveForward(float amount);
	void moveUp(float amount);
	void moveSide(float amount);
	void moveRelativeVec(glm::vec3 translation);

	//Rotate transform facing
	void rotateH(float amount);	//around Y axis
	void rotateP(float amount);	//around Z axis
	void rotateR(float amount);	//around X axis

	//Various vectors of the transform
	glm::vec3 forwardVector();
	glm::vec3 sideVector();
	glm::vec3 upVector();
};

