#include "Light.h"


Light::Light(void)
{
	this->color = glm::vec3(1.0f,1.0f,1.0f);
	this->brightness = 40.0f;
}


Light::~Light(void)
{
}

void Light::update(double deltaT) {
	
}