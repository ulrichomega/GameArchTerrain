#include "Transform.h"


Transform::Transform(void)
{
	this->transformMatrix = glm::mat4(1.0f);
}


Transform::~Transform(void)
{
}

void Transform::moveX(float amount) {
	this->transformMatrix = glm::translate(this->transformMatrix,glm::vec3(1,0,0));
}
void Transform::moveY(float amount) {
	this->transformMatrix = glm::translate(this->transformMatrix,glm::vec3(0,1,0));
}
void Transform::moveZ(float amount) {
	this->transformMatrix = glm::translate(this->transformMatrix,glm::vec3(0,0,1));
}


void Transform::moveForward(float amount) {
	glm::vec3 forwardVector = (glm::vec3)(this->transformMatrix * glm::vec4(1,0,0,0));
	this->transformMatrix = glm::translate(this->transformMatrix,forwardVector);
}
void Transform::moveUp(float amount) {
	glm::vec3 upVector = (glm::vec3)(this->transformMatrix * glm::vec4(0,1,0,0));
	this->transformMatrix = glm::translate(this->transformMatrix,upVector);
}
void Transform::moveSide(float amount) {
	glm::vec3 sideVector = (glm::vec3)(this->transformMatrix * glm::vec4(0,0,1,0));
	this->transformMatrix = glm::translate(this->transformMatrix,sideVector);
}

void Transform::rotateH(float amount) {
	this->transformMatrix = glm::rotate(this->transformMatrix, amount,glm::vec3(0,1,0));
}
void Transform::rotateP(float amount) {
	this->transformMatrix = glm::rotate(this->transformMatrix, amount,glm::vec3(0,0,1));
}
void Transform::rotateR(float amount) {
	this->transformMatrix = glm::rotate(this->transformMatrix, amount,glm::vec3(1,0,0));
}


glm::vec3 Transform::forwardVector() {
	return (glm::vec3)(this->transformMatrix * glm::vec4(1,0,0,0));
}
glm::vec3 Transform::sideVector(){
	return (glm::vec3)(this->transformMatrix * glm::vec4(1,0,0,0));
}
glm::vec3 Transform::upVector(){
	return (glm::vec3)(this->transformMatrix * glm::vec4(1,0,0,0));
}