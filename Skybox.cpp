#include "Skybox.h"
#include "CubeMap.h"

Skybox::Skybox(void)
{
	this->mesh = new CubeMap(this, "sky");
}
Skybox::Skybox(std::string textureNameBase) {
	this->mesh = new CubeMap(this, textureNameBase);
	this->transform.scale(10);
}


Skybox::~Skybox(void)
{
	delete this->mesh;
}

void Skybox::update(double deltaT) {
}
void Skybox::draw(){
	this->mesh->draw();
	std::cout << "I drew the skybox!" << std::endl;
}