#include "Mesh.h"

#include "EngineData.h"
#include "GameObject.h"
#include "BasicShaderProgram.h"
#include "UtilityFunctions.h"

Mesh::Mesh(void) 
{
}

Mesh::Mesh(GameObject* owner)
{
	this->owner = owner;
	this->createMesh();
	EngineData::addMesh(this);
}


Mesh::~Mesh(void)
{
	EngineData::removeMesh(this);
	delete this->shader;
}

void Mesh::draw() {
	glUseProgram(this->shader->programID);
	checkGLError("Could not use shader program");
	
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vertexIndexID);
	glBindVertexArray(this->vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER,this->vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->vertexIndexID);
	checkGLError("Could not bind buffers to be active");

	this->shader->updateUniforms();

	glDrawElements(GL_TRIANGLES, this->vertexIndices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	checkGLError("Could not draw mesh");
	std::cout << "Finished drawing a mesh" << std::endl;

	//Unbind program and buffer
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void Mesh::createMesh() {
	//Currently hardcoded for testing purposes;
	this->loadOBJ("data/container.obj");

	this->createShader();

	this->createBuffers();

	//Note: createTexture will eventually be used by loadOBJ, but today is not that day
	this->createTexture("data/container_diffuse.tga");
}
void Mesh::createShader() {
	//Note: This mesh currently is hard-coded to use the basic shaders
	this->shader = new BasicShaderProgram(this,"basic.fs","basic.vs");
}
//Creates the Vertex Array Object, and Vertex Buffer Objects for the mesh
void Mesh::createBuffers() {
	
	//Generate and fill vertex buffer object
	glGenBuffers(1, &this->vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
	checkGLError("Could not generate the VertexBuffer");
	glBufferData(GL_ARRAY_BUFFER, (sizeof(this->vertices[0])*this->vertices.size()), (GLvoid*)&this->vertices[0], GL_STATIC_DRAW);
	checkGLError("Could not fill VertexBuffer");

	//Generate and fill the vertex index buffer
	glGenBuffers(1, &this->vertexIndexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vertexIndexID);
	checkGLError("Could not generate the VertexIndexBuffer");
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(GLuint)*this->vertexIndices.size()), (GLvoid*)&this->vertexIndices[0], GL_STATIC_DRAW);
	checkGLError("Could not fill the VertexIndexBuffer");

	//Generate Vertex Array Object
	glGenVertexArrays(1, &this->vertexArrayID);
	glBindVertexArray(this->vertexArrayID);
	checkGLError("Could not generate and bind VertexArray");

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
	this->shader->linkVertexAttributes();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vertexIndexID);

	//Unbind the buffers
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}
void Mesh::createTexture(std::string filename) {
	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
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
}

//Loads an OBJ file into this mesh
//Does not currently account for textures
void Mesh::loadOBJ(std::string fileName) {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::ifstream objFile(fileName, std::ios::in);
	if (!objFile.is_open()) {
		std::cout << "Failed to open the file " << fileName << std::endl;
	}
	
	std::string line;
	
	while (getline(objFile,line)) {
		if (line.length() == 0) {	//Line was empty, for some reason
			continue;
		}

		std::stringstream lineStream(line);	//Possible performance issues
		std::string lineType;
		
		lineStream >> lineType;

		if (lineType == "v") {	//We're dealing with a vertex
			float x,y,z;
			lineStream >> x >> y >> z;
			vertices.push_back(glm::vec3(x,y,z));
		}
		else if (lineType == "vt") {	//"" UV
			float s, t;
			lineStream >> s >> t;
			uvs.push_back(glm::vec2(s,t));
		}
		else if (lineType == "vn") {	//"" Normal
			float x,y,z;
			lineStream >> x >> y >> z;
			normals.push_back(glm::vec3(x,y,z));
		}
		//Going to leave textures built into the obj for later
		//if (lineType == "mtllib") {
			
		//}
		else if (lineType == "f") {	//"" Face, uses data gathered above to construct a face in the buffer objects
			char* tempNum = new char[15];	//Holds the data from the sstream

			for (int i=0; i<3;i++) {
				lineStream.get(tempNum,15,'/');	//Get the vert number
				lineStream.ignore(1);	//Ignore the '/'
				int vertNum = atoi(tempNum);
				
				lineStream.get(tempNum,15,'/');	//Get the uv number
				lineStream.ignore(1);	//Ignore the '/'
				int uvNum = atoi(tempNum);
				
				lineStream.get(tempNum,15,' ');	//Get the normal number
				lineStream.ignore(1);	//Ignore the '/'
				int normalNum = atoi(tempNum);

				//Decrement all of these because obj files are evil
				vertNum--;
				uvNum--;
				normalNum--;

				vertex tempVert = { 
					{vertices[vertNum][0],vertices[vertNum][1],vertices[vertNum][2]}, //Position
					{uvs[uvNum][0],uvs[uvNum][1]}, //UV
					{normals[normalNum][0],normals[normalNum][1],normals[normalNum][2]}	//Normal
				};

				bool matchFound = false;

				//Check this->vertices to make sure we don't have duplicate data
				for (unsigned int i=0; i<this->vertices.size();i++){
					if (this->vertices[i]==tempVert) {	//The vert matches an already existing one
						this->vertexIndices.push_back(i);
						matchFound = true;
						break;
					}
				}
				if (!matchFound) {
					this->vertices.push_back(tempVert);
					this->vertexIndices.push_back(this->vertices.size()-1);
				}
			}
		}

	}

	//The below code is preserved in memoriam of 9 hours spent trying to fix a typo

	//this->vertices.clear();
	//this->vertexIndices.clear();

	//vertex tempVert = {{50.0f,50.0f,50.0f},{1.0f,1.0f},{0.0f,1.0f,1.0f}};
	//this->vertices.push_back(tempVert);
	//vertex tempVert2 = {{50.0f,50.0f,-50.0f},{1.0f,1.0f},{0.0f,1.0f,1.0f}};
	//this->vertices.push_back(tempVert2);
	//vertex tempVert3 = {{50.0f,-50.0f,50.0f},{1.0f,1.0f},{0.0f,1.0f,1.0f}};
	//this->vertices.push_back(tempVert3);
	//vertex tempVert99 = {{50.0f,-50.0f,-50.0f},{1.0f,1.0f},{0.0f,1.0f,1.0f}};
	//this->vertices.push_back(tempVert99);
	//
	//vertex tempVert4 = {{-50.0f,50.0f,50.0f},{1.0f,1.0f},{0.0f,0.0f,1.0f}};
	//this->vertices.push_back(tempVert4);
	//vertex tempVert5 = {{-50.0f,50.0f,-50.0f},{1.0f,1.0f},{0.0f,0.0f,1.0f}};
	//this->vertices.push_back(tempVert5);
	//vertex tempVert6 = {{-50.0f,-50.0f,50.0f},{1.0f,1.0f},{0.0f,0.0f,1.0f}};
	//this->vertices.push_back(tempVert6);
	//vertex tempVert7 = {{-50.0f,-50.0f,-50.0f},{1.0f,1.0f},{0.0f,0.0f,1.0f}};
	//this->vertices.push_back(tempVert7);
	//
	//vertex tempVert8 = {{50.0f,50.0f,50.0f},{1.0f,1.0f},{0.0f,1.0f,0.0f}};
	//this->vertices.push_back(tempVert8);
	//vertex tempVert9 = {{-50.0f,50.0f,50.0f},{1.0f,1.0f},{0.0f,1.0f,0.0f}};
	//this->vertices.push_back(tempVert9);
	//vertex tempVert13 = {{50.0f,-50.0f,50.0f},{1.0f,1.0f},{0.0f,1.0f,0.0f}};
	//this->vertices.push_back(tempVert13);
	//vertex tempVert14 = {{-50.0f,-50.0f,50.0f},{1.0f,1.0f},{0.0f,1.0f,0.0f}};
	//this->vertices.push_back(tempVert14);
	//
	//vertex tempVert23 = {{50.0f,50.0f,-50.0f},{1.0f,1.0f},{1.0f,0.0f,1.0f}};
	//this->vertices.push_back(tempVert23);
	//vertex tempVert33 = {{-50.0f,50.0f,-50.0f},{1.0f,1.0f},{1.0f,0.0f,1.0f}};
	//this->vertices.push_back(tempVert33);
	//vertex tempVert43 = {{50.0f,-50.0f,-50.0f},{1.0f,1.0f},{1.0f,0.0f,1.0f}};
	//this->vertices.push_back(tempVert43);
	//vertex tempVert53 = {{-50.0f,-50.0f,-50.0f},{1.0f,1.0f},{1.0f,0.0f,1.0f}};
	//this->vertices.push_back(tempVert53);

	//this->vertexIndices.push_back(2);
	//this->vertexIndices.push_back(0);
	//this->vertexIndices.push_back(1);
	//this->vertexIndices.push_back(2);
	//this->vertexIndices.push_back(3);
	//this->vertexIndices.push_back(1);
	//
	//this->vertexIndices.push_back(6);
	//this->vertexIndices.push_back(4);
	//this->vertexIndices.push_back(5);
	//this->vertexIndices.push_back(6);
	//this->vertexIndices.push_back(7);
	//this->vertexIndices.push_back(5);
	//
	//this->vertexIndices.push_back(10);
	//this->vertexIndices.push_back(8);
	//this->vertexIndices.push_back(9);
	//this->vertexIndices.push_back(10);
	//this->vertexIndices.push_back(11);
	//this->vertexIndices.push_back(9);
	//
	//this->vertexIndices.push_back(14);
	//this->vertexIndices.push_back(12);
	//this->vertexIndices.push_back(13);
	//this->vertexIndices.push_back(14);
	//this->vertexIndices.push_back(15);
	//this->vertexIndices.push_back(13);
}

Transform* Mesh::getTransform() {
	return &this->owner->transform;
}