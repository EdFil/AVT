#include "ButtonTextureProgram.h"

ButtonTextureProgram::ButtonTextureProgram(std::string name, std::string vertexFile, std::string fragmentFile) : Program(name, vertexFile, fragmentFile) {
	//Empty
}

void ButtonTextureProgram::createShaderProgram() {
	printf("Inicio %d\n", isOpenGLError());
	_vertexShaderId = loadShaderFromFile(_vertexFile, VERTEX);
	_fragmentShaderId = loadShaderFromFile(_fragmentFile, FRAGMENT);
	printf("%d\n", isOpenGLError());
	_programId = glCreateProgram();
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);
	printf("%d\n", isOpenGLError());
	glBindAttribLocation(_programId, 0, "in_Position");
	glBindAttribLocation(_programId, 1, "in_UV");
	printf("%d\n", isOpenGLError());
	glLinkProgram(_programId);
	printf("%d\n", isOpenGLError());
	_colorUniformId = glGetUniformLocation(_programId, "Color");
	printf("%d\n", isOpenGLError());
	_textureUniformId = glGetUniformLocation(_programId, "Textura");
	printf("FIM %d\n", isOpenGLError());
}