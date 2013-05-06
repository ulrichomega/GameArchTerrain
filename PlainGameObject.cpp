#include "PlainGameObject.h"
#include "Mesh.h"

PlainGameObject::PlainGameObject(void)
{
	this->mesh = new Mesh(this);
}

PlainGameObject::PlainGameObject(std::string objFile, std::string diffuseFile, std::string normalFile)
{
	this->mesh = new Mesh(this, objFile, diffuseFile, normalFile);
}


PlainGameObject::~PlainGameObject(void)
{
	delete this->mesh;
}

void PlainGameObject::update(double deltaT) {

}

void PlainGameObject::draw() {
	this->mesh->draw();
}