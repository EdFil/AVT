#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include "GL\glew.h"
#include "GL\freeglut.h"

class Program {

	std::string _vertexFile, _fragmentFile;

	std::string _name;
	GLuint _programId;
	GLuint _vertexShaderId;
	GLuint _fragmentShaderId;
	GLuint _modelMatrixUniformId;
	GLuint _sharedMatrixUboId;

	char* _vertexShader;
	char* _fragmentShader;

public:
	Program(std::string name, std::string vertexFile, std::string fragmentFile);

	void bind() const ;

	void createShaderProgram();
	void destroyShaderProgram();

	GLuint loadShaderFromFile(std::string fileName, GLenum shaderType);

	GLuint getModelMatrixUniformId() const  { return _modelMatrixUniformId; }
	GLuint getSharedMatrixUboId() const { return _sharedMatrixUboId; }
	GLuint getProgramId() const { return _programId; }

};

#endif
