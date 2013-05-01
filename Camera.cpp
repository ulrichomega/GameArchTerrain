#include "Camera.h"


Camera::Camera(void)
{
	this->ProjectionMatrix = glm::perspective(90.0f,1.0f, 0.1f, 100.0f);
	this->transformMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 15.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0));
}


Camera::~Camera(void)
{
}

void Camera::moveX(float amount) {
	this->transformMatrix = glm::translate(this->transformMatrix,glm::vec3(1,0,0));
}
void Camera::moveY(float amount) {
	this->transformMatrix = glm::translate(this->transformMatrix,glm::vec3(0,1,0));
}
void Camera::moveZ(float amount) {
	this->transformMatrix = glm::translate(this->transformMatrix,glm::vec3(0,0,1));
}


void Camera::moveForward(float amount) {
	glm::vec3 forwardVector = (glm::vec3)(this->transformMatrix * glm::vec4(1,0,0,0));
	this->transformMatrix = glm::translate(this->transformMatrix,forwardVector);
}
void Camera::moveUp(float amount) {
	glm::vec3 upVector = (glm::vec3)(this->transformMatrix * glm::vec4(0,1,0,0));
	this->transformMatrix = glm::translate(this->transformMatrix,upVector);
}
void Camera::moveSide(float amount) {
	glm::vec3 sideVector = (glm::vec3)(this->transformMatrix * glm::vec4(0,0,1,0));
	this->transformMatrix = glm::translate(this->transformMatrix,sideVector);
}

void Camera::rotateH(float amount) {
	this->transformMatrix = glm::rotate(this->transformMatrix, amount,glm::vec3(0,1,0));
}
void Camera::rotateP(float amount) {
	this->transformMatrix = glm::rotate(this->transformMatrix, amount,glm::vec3(0,0,1));
}
void Camera::rotateR(float amount) {
	this->transformMatrix = glm::rotate(this->transformMatrix, amount,glm::vec3(1,0,0));
}