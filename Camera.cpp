#include "Camera.h"


Camera::Camera(void) : maxVelocity(10.0f)
{
	this->ProjectionMatrix = glm::perspective(60.0f, 1.0f, 0.1f, 100.f);

	this->transform.setTransformMatrix( glm::lookAt(glm::vec3(0.0, 0.0, 15.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)));
	this->velocity = glm::vec3(0.0f,0.0f,0.0f);

	this->rotateHSpeed = 10.0f;
	this->rotatePSpeed = 10.0f;
}


Camera::~Camera(void)
{
}

void Camera::update(double deltaT) {
	this->updateMove(deltaT);
	this->updateRotate(deltaT);
}

void Camera::updateMove(double deltaT) {
		//Construct a velocity vector that will be added to the current velocity
	glm::vec3 additionalVelocity(0.0f,0.0f,0.0f);
	if (GLFW_PRESS == glfwGetKey(EngineData::getActionKey("forward"))) {
		additionalVelocity += glm::vec3(0.0f,0.0f,1.0f*deltaT);
	}
	if (GLFW_PRESS == glfwGetKey(EngineData::getActionKey("back"))) {
		additionalVelocity += glm::vec3(0.0f,0.0f,-1.0f*deltaT);
	}
	if (GLFW_PRESS == glfwGetKey(EngineData::getActionKey("left"))) {
		additionalVelocity += glm::vec3(1.0f*deltaT,0.0f,0.0f);
	}
	if (GLFW_PRESS == glfwGetKey(EngineData::getActionKey("right"))) {
		additionalVelocity += glm::vec3(-1.0f*deltaT,0.0f,0.0f);
	}

	if (additionalVelocity.x == 0.0f && additionalVelocity.y == 0.0f
			&& additionalVelocity.z == 0.0f) {
		this->velocity.x *= 0.95f;
		this->velocity.y *= 0.95f;
		this->velocity.z *= 0.95f;
	}
	else {
		//Apply the velocity added this tick
		additionalVelocity *= deltaT;
		this->velocity += additionalVelocity;
		if (this->velocity.length() > this->maxVelocity ) {
			glm::clamp(this->velocity,0.0f,this->maxVelocity);
		}
	}
	this->transform.moveRelativeVec(this->velocity);

	//std::cout << "Moving camera at (" << this->velocity.x << ", " 
	//	<< this->velocity.y << ", " << this->velocity.z << ")" << std::endl;

}

void Camera::updateRotate(double deltaT){
	glm::vec2 mouseDelta = EngineData::getMouseDelta();

	this->transform.rotateH(mouseDelta.x*deltaT);
	this->transform.rotateP(mouseDelta.y*deltaT);
}