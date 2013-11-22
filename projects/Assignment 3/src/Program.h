#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include "GL\glew.h"
#include "GL\freeglut.h"

class Program {

	std::string _vertexFile, _fragmentFile;

	GLuint _programId;
	GLuint _vertexShaderId;
	GLuint _fragmentShaderId;
	GLuint _uniformId;
	GLuint _uboId;

	char* _vertexShader;
	char* _fragmentShader;

public:
	Program(char* vertexFile, char* fragmentFile);

	void createShaderProgram();
	void destroyShaderProgram();

	GLuint loadShaderFromFile(std::string fileName, GLenum shaderType);

	GLuint getUboId() const  { return _uboId; }
	GLuint getUniformId() const { return _uniformId; }
	GLuint getProgramId() const { return _programId; }

};

#endif
