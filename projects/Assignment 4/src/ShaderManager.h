#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <map>
#include "Program.h"
#include "SimpleProgram.h"
#include "TextureProgram.h"
#include "ButtonTextureProgram.h"

class ShaderManager {

	//Name of program as key and program as value
	std::map<std::string, Program*> _programList;

public:
	ShaderManager();

	//Getters
	Program* getProgram(std::string name);
	Program* getProgram(int index);

	//Adding new Program
	void addSimpleProgram(std::string vertexFile, std::string fragmentFile);
	void addSimpleProgram(std::string name, std::string vertexFile, std::string fragmentFile);
	void addTextureProgram(std::string vertexFile, std::string fragmentFile);
	void addTextureProgram(std::string name, std::string vertexFile, std::string fragmentFile);
	void addButtonTextureProgram(std::string vertexFile, std::string fragmentFile);
	void addButtonTextureProgram(std::string name, std::string vertexFile, std::string fragmentFile);
	
	//Compile and destroy shaders
	void createShaderProgram();
	void destroyShaderProgram();

	//Selecting shaders
	int bindAndGetUniform(int index);
	int bindAndGetUniform(std::string name);
	void unBind();

};



#endif
