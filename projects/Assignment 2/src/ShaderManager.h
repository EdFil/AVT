#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <vector>

#include "Program.h"

class ShaderManager {

	GLuint _selectedShader;
	std::vector<Program*> _programList;

public:
	ShaderManager();
	void addProgram(char* vertexFile, char* fragmentFile);
	void createShaderProgram();
	void destroyShaderProgram();

	GLuint getSelectedShader() { return _programList[_selectedShader]->getProgramId(); }
	GLuint getSelectedUniformId() { return _programList[_selectedShader]->getUniformId(); }
	void setSelectedShader(GLuint shader){ _selectedShader = shader; }
};



#endif
