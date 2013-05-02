#include "Camera.h"


Camera::Camera(void)
{
	this->ProjectionMatrix = glm::perspective(90.0f,1.0f, 0.1f, 100.0f);
}


Camera::~Camera(void)
{
}

void Camera::update(double deltaT) {

}