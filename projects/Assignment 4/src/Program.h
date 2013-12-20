#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include "GL\glew.h"
#include "GL\freeglut.h"

#define VERTEX GL_VERTEX_SHADER
#define FRAGMENT GL_FRAGMENT_SHADER

class Program {

protected:
	std::string _vertexFile, _fragmentFile;

	std::string _name;
	GLuint _programId;
	GLuint _vertexShaderId;
	GLuint _fragmentShaderId;

	char* _vertexShader;
	char* _fragmentShader;

public:
	Program(std::string name, std::string vertexFile, std::string fragmentFile);

	void bind() const ;
	void destroyShaderProgram();

	GLuint getProgramId() const { return _programId; }

	//Virtual Methods
	virtual void createShaderProgram() = 0;

protected:
	GLuint loadShaderFromFile(std::string fileName, GLenum shaderType);

};

#endif
