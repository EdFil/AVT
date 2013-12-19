#include <fstream>
#include "SimpleProgram.h"
#include <iostream>
#include <vector>

SimpleProgram::SimpleProgram(std::string name, std::string vertexFile, std::string fragmentFile) : Program(name, vertexFile, fragmentFile){
}

void SimpleProgram::createShaderProgram() {
	_vertexShaderId = loadShaderFromFile(_vertexFile, VERTEX);
	_fragmentShaderId = loadShaderFromFile(_fragmentFile, FRAGMENT);
	_programId = glCreateProgram();
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);
	glBindAttribLocation(_programId, 0, "in_Position");
	glLinkProgram(_programId);
	_modelMatrixUniformId = glGetUniformLocation(_programId, "ModelMatrix");
	_colorUniformId = glGetUniformLocation(_programId, "Color");
	_sharedMatrixUboId = glGetUniformBlockIndex(_programId, "SharedMatrices");
	glUniformBlockBinding(_programId, _sharedMatrixUboId, 0);
}
