#include "shader.h"


shader::shader(void)
{
}

shader::shader(const char* filename, GLenum shader_type)
{
}


shader::~shader(void)
{
}


//Professor Destefano's Load Shader code
void shader::LoadShader(const char* filename, GLenum shader_type)
{
	//GLuint shader_id = 0;
	//FILE* file;
	//long file_size = -1;
	//GLchar* glsl_source;
 //   fprintf(stderr, "name: %s\n",filename);

	//if (NULL != (file = fopen(filename, "rb")) &&
	//	0 == fseek(file, 0, SEEK_END) &&
	//	-1 != (file_size = ftell(file)))
	//{
	//	rewind(file);
	//	
	//	if (NULL != (glsl_source = (GLchar*)malloc(file_size + 1)))
	//	{
	//		if (file_size == (long)fread(glsl_source, sizeof(GLchar), file_size, file))
	//		{
	//			glsl_source[file_size] = '\0';
 //               const GLchar* glsl_source_c = glsl_source;
	//			//fprintf(stderr, "Source: %s\n", glsl_source_c);

	//			if (0 != (shader_id = glCreateShader(shader_type)))
	//			{
	//				glShaderSource(shader_id, 1, &glsl_source_c, NULL);
	//				glCompileShader(shader_id);
	//				fprintf(stderr,"Could not compile the shader");
	//			}
	//			else
	//				fprintf(stderr, "ERROR: Could not create the shader.\n");
	//		}
	//		else
	//			fprintf(stderr, "ERROR: Could not read file %s\n", filename);

	//		free(glsl_source);
	//	}
	//	else
	//		fprintf(stderr, "ERROR: Could not allocate %li bytes.\n", file_size);

	//	fclose(file);
	//}
	//else
	//	fprintf(stderr, "ERROR: Could not open file %s\n", filename);

	//this->shaderID = shader_id;
}