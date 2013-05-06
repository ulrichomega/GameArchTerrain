#include "heightMap.h"

#include "EngineData.h"
#include "GameObject.h"
#include "ColorShaderProgram.h"
#include "UtilityFunctions.h"
#include "Mesh.h"

heightMap::heightMap(void)
{
}

heightMap::heightMap(GameObject* owner, std::string heightMapFilename){
	this->owner = owner;
	this->xSize = 64;
	this->ySize = 64;

	this->createMesh(heightMapFilename);
}

heightMap::~heightMap(void)
{
}

void heightMap::createMesh(std::string heightMapFilename){
	this->createVertices(heightMapFilename);

	this->createShader();
	this->createBuffers();
}

void heightMap::createVertices(std::string heightMapFilename) {
	GLFWimage imageData;
	if (GL_FALSE == glfwReadImage("data/Starfield.tga",&imageData,0)){
		exit(EXIT_FAILURE);
	}
	
	for(unsigned int x=0; x<this->xSize; x++) {
		for(unsigned int y=0; y<this->ySize; y++) {
			float r = imageData.Data[x*imageData.BytesPerPixel + y*imageData.BytesPerPixel + 0];
			float g = imageData.Data[x*imageData.BytesPerPixel + y*imageData.BytesPerPixel + 1];
			float b = imageData.Data[x*imageData.BytesPerPixel + y*imageData.BytesPerPixel + 2];

			float average = (r+g+b)/3.0f;
			vertex temp = {{x-this->xSize/2,average,y-this->ySize/2},	//position
						{0.0f,1.0f},		//UV
						{0.0f,1.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f},		//Bitangent
						{r/255,g/255,b/255}		//Color
			};
			this->vertices.push_back(temp);
		}
	}
	
	for(unsigned int x=0; x<this->xSize-1; x++) {
		for(unsigned int y=0; y<this->ySize-1; y++) {
			//Construct square with lowerleft corner at x,y (more efficient triangle storage methods coming soon)
			//Triangle 1
			this->vertexIndices.push_back(x+y*this->ySize);
			this->vertexIndices.push_back(x+1+y*this->ySize);
			this->vertexIndices.push_back(x+(y+1)*this->ySize);

			//Triangle 2 
			this->vertexIndices.push_back(x+1+(y+1)*this->ySize);
			this->vertexIndices.push_back(x+1+y*this->ySize);
			this->vertexIndices.push_back(x+(y+1)*this->ySize);
		}
	}
	glfwFreeImage(&imageData);
	this->calculateColor();
}

void heightMap::createShader() {
	this->shader = new ColorShaderProgram(this);
}

void heightMap::draw() {
	glDisable(GL_CULL_FACE);
	

	glUseProgram(this->shader->programID);
	checkGLError("Could not use shader program");
	
	//Bind all buffers and textures
	glBindVertexArray(this->vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER,this->vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->vertexIndexID);
	checkGLError("Could not bind buffers to be active");
	
	//Bind textures to gl active textures
	glActiveTexture(GL_TEXTURE0);	//diffuse
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	this->shader->setTextureUnit(0,0);
	glActiveTexture(GL_TEXTURE1);	//normal
	glBindTexture(GL_TEXTURE_2D, this->normalMapID);
	this->shader->setTextureUnit(1,1);

	this->shader->updateUniforms();
	this->shader->enableVertexAttribArray();

	glDrawElements(GL_TRIANGLES, this->vertexIndices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	checkGLError("Could not draw mesh");

	//Unbind program and buffer
	this->shader->disableVertexAttribArray();
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	checkGLError("Could not unbind buffers");

	//Unbind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	checkGLError("Could not unbind textures");
	
	glEnable(GL_CULL_FACE);
}

void heightMap::calculateColor() {
	for(unsigned int x=1; x<this->xSize-1; x++) {
		for(unsigned int y=1; y<this->ySize-1; y++) {
			//this->vertices[x+y*this->ySize].color = {
			//Can be used to calculate with slopes, as well (but not now)
		}
	}

}