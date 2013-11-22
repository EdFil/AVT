#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <vector>

#include "Program.h"

class ShaderManager {

	GLuint _selectedProgram;
	GLuint _selectedProgramId;
	GLuint _selectedUniformId;
	std::vector<Program> _programList;

public:
	ShaderManager();
	void addProgram(char* vertexFile, char* fragmentFile);
	void createShaderProgram();
	void destroyShaderProgram();

	const GLuint getSelectedProgram() const { return _selectedProgramId; }
	const GLuint getSelectedUniformId() const { return _selectedUniformId; }
	inline void setProgram(GLuint id){ 
		_selectedProgram = id;
		_selectedProgramId = _programList[id].getProgramId(); 
		_selectedUniformId = _programList[id].getUniformId(); 
	}
};



#endif
