#ifndef SIMPLE_PROGRAM_H
#define SIMPLE_PROGRAM_H

#include "Program.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include <string>

#define VERTEX GL_VERTEX_SHADER
#define FRAGMENT GL_FRAGMENT_SHADER

class SimpleProgram : public Program {

private:
	GLuint _modelMatrixUniformId;
	GLuint _colorUniformId;
	GLuint _sharedMatrixUboId;


public:
	SimpleProgram(std::string name, std::string vertexFile, std::string fragmentFile);

	void createShaderProgram();

	GLuint getColorUniformId() const  { return _colorUniformId; }
	GLuint getModelMatrixUniformId() const  { return _modelMatrixUniformId; }
	GLuint getSharedMatrixUboId() const { return _sharedMatrixUboId; }

};

#endif
