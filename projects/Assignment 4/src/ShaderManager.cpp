#include "ShaderManager.h"

ShaderManager::ShaderManager(){

}

void ShaderManager::addProgram(std::string vertexFile, std::string fragmentFile){
	int foundIndex = std::string(vertexFile).find_last_of("/");
	addProgram(std::string(vertexFile).substr(foundIndex+1), vertexFile, fragmentFile);
}

void ShaderManager::addProgram(std::string name, std::string vertexFile, std::string fragmentFile){
	if(_programList.find(name) == _programList.end())
		_programList.insert(std::pair<std::string, Program>(name, Program(name, vertexFile, fragmentFile)));
}

void ShaderManager::createShaderProgram(){
	for(std::map<std::string,Program>::iterator it=_programList.begin(); it!=_programList.end(); ++it)
		it->second.createShaderProgram();
}

void ShaderManager::destroyShaderProgram(){
	glUseProgram(0);
	for(std::map<std::string,Program>::iterator it=_programList.begin(); it!=_programList.end(); ++it)
		it->second.destroyShaderProgram();
}

Program *ShaderManager::getProgram(int index){
	std::map<std::string,Program>::iterator it = _programList.begin();
	for(int i = 0; i != index; i++, it++);
	return &(it->second);
}


Program *ShaderManager::getProgram(std::string name){
	return &_programList.find(name)->second;
}