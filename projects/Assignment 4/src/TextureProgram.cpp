#include "TextureProgram.h"

TextureProgram::TextureProgram(std::string name, std::string vertexFile, std::string fragmentFile) : Program(name, vertexFile, fragmentFile) {
	//Empty
}

void TextureProgram::createShaderProgram() {
	_vertexShaderId = loadShaderFromFile(_vertexFile, VERTEX);
	_fragmentShaderId = loadShaderFromFile(_fragmentFile, FRAGMENT);
	_programId = glCreateProgram();
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);
	glBindAttribLocation(_programId, 0, "in_Position");
	glBindAttribLocation(_programId, 1, "in_Normal");
	glBindAttribLocation(_programId, 2, "in_UV");
	glLinkProgram(_programId);
	_modelMatrixUniformId = glGetUniformLocation(_programId, "ModelMatrix");
	_colorUniformId = glGetUniformLocation(_programId, "Color");
	_sharedMatrixUboId = glGetUniformBlockIndex(_programId, "SharedMatrices");
	_textureUniformId = glGetUniformLocation(getProgramId(), "Texture");
	glUniformBlockBinding(_programId, _sharedMatrixUboId, 0);
}