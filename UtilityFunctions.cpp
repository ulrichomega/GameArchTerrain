#include "UtilityFunctions.h"

//Queries OpenGL to see if an error has been reported. 
//If it has, output to console
void checkGLError(std::string errorString) {
	GLenum errorValue = glGetError();
	while (errorValue != GL_NO_ERROR) {
		std::cout << std::endl << errorString << ": " << gluErrorString(errorValue) << std::endl;
		errorValue = glGetError();
	}
}