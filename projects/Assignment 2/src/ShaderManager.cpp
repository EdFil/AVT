#include "ShaderManager.h"

ShaderManager::ShaderManager() : _selectedShader(0) {}

void ShaderManager::addProgram(char* vertexFile, char* fragmentFile){
	Program* program = new Program(vertexFile, fragmentFile);
	_programList.push_back(program);
}

void ShaderManager::createShaderProgram(){
	for(unsigned int i = 0; i < _programList.size(); i++)
		_programList[i]->createShaderProgram();
}

void ShaderManager::destroyShaderProgram(){
	glUseProgram(0);
	for(unsigned int i = 0; i < _programList.size(); i++)
		_programList[i]->destroyShaderProgram();
}