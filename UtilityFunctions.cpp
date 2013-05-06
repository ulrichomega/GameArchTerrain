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

//Code from: http://www.dreamincode.net/forums/topic/66480-perlin-noise/
double findnoise2(double x,double y)
{
 int n=(int)x+(int)y*57;
 n=(n<<13)^n;
 int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;
 return 1.0-((double)nn/1073741824.0);
}

