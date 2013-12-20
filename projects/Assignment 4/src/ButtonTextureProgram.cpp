#include "ButtonTextureProgram.h"

ButtonTextureProgram::ButtonTextureProgram(std::string name, std::string vertexFile, std::string fragmentFile) : Program(name, vertexFile, fragmentFile) {
	//Empty
}

void ButtonTextureProgram::createShaderProgram() {
	_vertexShaderId = loadShaderFromFile(_vertexFile, VERTEX);
	_fragmentShaderId = loadShaderFromFile(_fragmentFile, FRAGMENT);
	_programId = glCreateProgram();
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);
	glBindAttribLocation(_programId, 0, "in_Position");
	glBindAttribLocation(_programId, 2, "in_UV");
	glLinkProgram(_programId);
	_colorUniformId = glGetUniformLocation(_programId, "Color");
	_textureUniformId = glGetUniformLocation(getProgramId(), "Texture");
}