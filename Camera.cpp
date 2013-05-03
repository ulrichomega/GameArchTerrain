#include "Camera.h"


Camera::Camera(void) : maxVelocity(10.0f)
{
	this->ProjectionMatrix = glm::perspective(90.0f,1.0f, 0.1f, 100.0f);
	this->velocity = glm::vec3(0.0f,0.0f,0.0f);
}


Camera::~Camera(void)
{
}

void Camera::update(double deltaT) {
	//Construct a velocity vector that will be added to the current velocity
	glm::vec3 additionalVelocity(0.0f,0.0f,0.0f);
	if (glfwGetKey(EngineData::getKey("forward"))) {
		additionalVelocity += glm::vec3(0.1f,0.0f,0.0f);
	}
	if (glfwGetKey(EngineData::getKey("back"))) {
		additionalVelocity += glm::vec3(-0.1f,0.0f,0.0f);
	}
	if (glfwGetKey(EngineData::getKey("left"))) {
		additionalVelocity += glm::vec3(0.0f,0.0f,-0.1f);
	}
	if (glfwGetKey(EngineData::getKey("right"))) {
		additionalVelocity += glm::vec3(0.0f,0.0f,0.1f);
	}

	//Apply the velocity added this tick
	additionalVelocity *= deltaT;
	this->velocity += additionalVelocity;
	if (this->velocity.length() > this->maxVelocity ) {
		glm::clamp(this->velocity,0.0f,this->maxVelocity);
	}
}