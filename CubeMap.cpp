#include "CubeMap.h"
#include "EngineData.h"
#include "GameObject.h"
#include "BasicShaderProgram.h"
#include "UtilityFunctions.h"
#include "Mesh.h"

CubeMap::CubeMap(void)
{
}

CubeMap::CubeMap(GameObject* owner, std::string textureNameBase) {
	this->owner = owner;
	this->createMesh(textureNameBase);
}

CubeMap::~CubeMap(void)
{
}

void CubeMap::createMesh(std::string textureNameBase) {
	std::string right = textureNameBase + "-right.tga";
	std::string left = textureNameBase + "-left.tga";
	std::string top = textureNameBase + "-top.tga";
	std::string bottom = textureNameBase + "-bottom.tga";
	std::string back = textureNameBase + "-back.tga";
	std::string front = textureNameBase + "-front.tga";

	this->createVertices();

	this->createTexture(0, right);
	this->createTexture(1, left);
	this->createTexture(2, top);
	this->createTexture(3, bottom);
	this->createTexture(4, back);
	this->createTexture(5, front);

	this->createShader();
	this->createBuffers();
	//int* temp = new int[this->vertexIndices.size()];
	//glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
	//glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(int)*this->vertexIndices.size(), temp);
	//for (int j = 0; j<this->vertexIndices.size(); j++) {
	//	std::cout << "Index" << j << ": (" << temp[j] << ")" << std::endl;
	//}
	//delete temp;
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void CubeMap::createVertices(){
	this->vertices.clear();
	this->vertexIndices.clear();
	this->createRightVertices();
	this->createLeftVertices();
	this->createTopVertices();
	this->createBottomVertices();
	this->createBackVertices();
	this->createFrontVertices();
}
void CubeMap::createTexture(int textureIndex, std::string filename) {
	glGenTextures(1, &this->textureID[textureIndex]);
	glBindTexture(GL_TEXTURE_2D, this->textureID[textureIndex]);
	checkGLError("Could not generate and bind the texture");

	//Note, the below should be fully customizable, but today is not that day
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	checkGLError("Could not set Texture parameters");

	//Load texture in and create mipmaps
	if (!glfwLoadTexture2D(filename.c_str(),0)) {
		std::cout << "Could not load texture: " << filename << std::endl;
		throw "Could not load texture";
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	checkGLError("Could not generate mipmaps");
	glBindTexture(GL_TEXTURE_2D, 0);
}
void CubeMap::createShader() {
	this->shader = new BasicShaderProgram(this);
}

void CubeMap::draw() {
	glDisable(GL_CULL_FACE);

	glUseProgram(this->shader->programID);
	checkGLError("Could not use shader program");
	
	//Bind all buffers and textures
	glBindVertexArray(this->vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER,this->vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->vertexIndexID);
	checkGLError("Could not bind buffers to be active");
	
	this->shader->updateUniforms();
	this->shader->enableVertexAttribArray();
	//
	//for (unsigned int i=0; i<6; i++) {
	//	//Bind textures to gl active textures
		glActiveTexture(GL_TEXTURE0);	//diffuse
		glBindTexture(GL_TEXTURE_2D, this->textureID[1]);
	//	this->shader->setTextureUnit(0,0);

		glDrawElements(GL_TRIANGLES, this->vertexIndices.size(), GL_UNSIGNED_INT, 0);
	//	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(i*6 + 3));
	//	checkGLError("Could not draw mesh");
	//}
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

void CubeMap::createRightVertices(){
	//Topleft
	vertex tlVertex = {{1.0f,1.0f,-1.0f},	//position
						{0.0f,1.0f},		//UV
						{-1.0f,0.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(tlVertex);
	//Topright
	vertex trVertex = {{1.0f,1.0f,1.0f},	//position
						{1.0f,1.0f},		//UV
						{-1.0f,0.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(trVertex);
	//Bottomleft
	vertex blVertex = {{1.0f,-1.0f,-1.0f},	//position
						{0.0f,0.0f},		//UV
						{-1.0f,0.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(blVertex);
	//Bottomright
	vertex brVertex = {{1.0f,-1.0f,1.0f},	//position
						{1.0f,0.0f},		//UV
						{-1.0f,0.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(brVertex);

	this->compileSideVerts();
}
void CubeMap::createLeftVertices(){
	//Topleft
	vertex tlVertex = {{-1.0f,1.0f,1.0f},	//position
						{0.0f,1.0f},		//UV
						{1.0f,0.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(tlVertex);
	//Topright
	vertex trVertex = {{-1.0f,1.0f,-1.0f},	//position
						{1.0f,1.0f},		//UV
						{1.0f,0.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(trVertex);
	//Bottomleft
	vertex blVertex = {{-1.0f,-1.0f,1.0f},	//position
						{0.0f,0.0f},		//UV
						{1.0f,0.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(blVertex);
	//Bottomright
	vertex brVertex = {{-1.0f,-1.0f,-1.0f},	//position
						{1.0f,0.0f},		//UV
						{1.0f,0.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(brVertex);

	this->compileSideVerts();
}
void CubeMap::createTopVertices(){
	//Topleft
	vertex tlVertex = {{-1.0f,1.0f,1.0f},	//position
						{0.0f,1.0f},		//UV
						{0.0f,-1.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(tlVertex);
	//Topright
	vertex trVertex = {{1.0f,1.0f,1.0f},	//position
						{1.0f,1.0f},		//UV
						{0.0f,-1.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(trVertex);
	//Bottomleft
	vertex blVertex = {{-1.0f,1.0f,-1.0f},	//position
						{0.0f,0.0f},		//UV
						{0.0f,-1.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(blVertex);
	//Bottomright
	vertex brVertex = {{1.0f,1.0f,-1.0f},	//position
						{1.0f,0.0f},		//UV
						{0.0f,-1.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(brVertex);

	this->compileSideVerts();
	}
void CubeMap::createBottomVertices(){
	//Topleft
	vertex tlVertex = {{-1.0f,-1.0f,-1.0f},	//position
						{0.0f,1.0f},		//UV
						{0.0f,1.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(tlVertex);
	//Topright
	vertex trVertex = {{1.0f,-1.0f,-1.0f},	//position
						{1.0f,1.0f},		//UV
						{0.0f,1.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(trVertex);
	//Bottomleft
	vertex blVertex = {{-1.0f,-1.0f,1.0f},	//position
						{0.0f,0.0f},		//UV
						{0.0f,1.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(blVertex);
	//Bottomright
	vertex brVertex = {{1.0f,-1.0f,1.0f},	//position
						{1.0f,0.0f},		//UV
						{0.0f,1.0f,0.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(brVertex);

	this->compileSideVerts();
}
void CubeMap::createBackVertices(){
	//Topleft
	vertex tlVertex = {{1.0f,1.0f,1.0f},	//position
						{0.0f,1.0f},		//UV
						{0.0f,1.0f,-1.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(tlVertex);
	//Topright
	vertex trVertex = {{-1.0f,1.0f,1.0f},	//position
						{1.0f,1.0f},		//UV
						{0.0f,1.0f,-1.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(trVertex);
	//Bottomleft
	vertex blVertex = {{1.0f,-1.0f,1.0f},	//position
						{0.0f,0.0f},		//UV
						{0.0f,1.0f,-1.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(blVertex);
	//Bottomright
	vertex brVertex = {{-1.0f,-1.0f,1.0f},	//position
						{1.0f,0.0f},		//UV
						{0.0f,0.0f,-1.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(brVertex);

	this->compileSideVerts();
}
void CubeMap::createFrontVertices(){
	//Topleft
	vertex tlVertex = {{-1.0f,1.0f,-1.0f},	//position
						{0.0f,1.0f},		//UV
						{0.0f,1.0f,1.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(tlVertex);
	//Topright
	vertex trVertex = {{1.0f,1.0f,-1.0f},	//position
						{1.0f,1.0f},		//UV
						{0.0f,1.0f,1.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(trVertex);
	//Bottomleft
	vertex blVertex = {{-1.0f,-1.0f,-1.0f},	//position
						{0.0f,0.0f},		//UV
						{0.0f,1.0f,1.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(blVertex);
	//Bottomright
	vertex brVertex = {{1.0f,-1.0f,-1.0f},	//position
						{1.0f,0.0f},		//UV
						{0.0f,0.0f,1.0f},		//Normals
						{0.0f,0.0f,0.0f},		//Tangent
						{0.0f,0.0f,0.0f}		//Bitangent
	};
	this->vertices.push_back(brVertex);

	this->compileSideVerts();
}

void CubeMap::compileSideVerts() {
	//std::cout << "Number of verts so far: " << this->vertices.size() << std::endl;

	this->vertexIndices.push_back(this->vertices.size()-4);
	this->vertexIndices.push_back(this->vertices.size()-2);
	this->vertexIndices.push_back(this->vertices.size()-3);

	//std::cout << "Added vertices indices: " << this->vertexIndices[this->vertexIndices.size()-3] << " " << this->vertexIndices[this->vertexIndices.size()-2] << " " << this->vertexIndices[this->vertexIndices.size()-1] << std::endl;
	//std::cout << "Index" << this->vertexIndices[this->vertexIndices.size()-3] << ": (" << this->vertices[this->vertexIndices[this->vertexIndices.size()-3]].position[0] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-3]].position[1] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-3]].position[2] << ")" << std::endl;
	//std::cout << "Index" << this->vertexIndices[this->vertexIndices.size()-2] << ": (" << this->vertices[this->vertexIndices[this->vertexIndices.size()-2]].position[0] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-2]].position[1] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-2]].position[2] << ")" << std::endl;
	//std::cout << "Index" << this->vertexIndices[this->vertexIndices.size()-1] << ": (" << this->vertices[this->vertexIndices[this->vertexIndices.size()-1]].position[0] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-1]].position[1] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-1]].position[2] << ")" << std::endl;

	this->vertexIndices.push_back(this->vertices.size()-1);
	this->vertexIndices.push_back(this->vertices.size()-3);
	this->vertexIndices.push_back(this->vertices.size()-2);
	//
	//std::cout << "Added vertices indices: " << this->vertexIndices[this->vertexIndices.size()-3] << " " << this->vertexIndices[this->vertexIndices.size()-2] << " " << this->vertexIndices[this->vertexIndices.size()-1] << std::endl;
	//std::cout << "Index" << this->vertexIndices[this->vertexIndices.size()-3] << ": (" << this->vertices[this->vertexIndices[this->vertexIndices.size()-3]].position[0] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-3]].position[1] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-3]].position[2] << ")" << std::endl;
	//std::cout << "Index" << this->vertexIndices[this->vertexIndices.size()-2] << ": (" << this->vertices[this->vertexIndices[this->vertexIndices.size()-2]].position[0] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-2]].position[1] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-2]].position[2] << ")" << std::endl;
	//std::cout << "Index" << this->vertexIndices[this->vertexIndices.size()-1] << ": (" << this->vertices[this->vertexIndices[this->vertexIndices.size()-1]].position[0] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-1]].position[1] << "," << this->vertices[this->vertexIndices[this->vertexIndices.size()-1]].position[2] << ")" << std::endl;
	//	
}