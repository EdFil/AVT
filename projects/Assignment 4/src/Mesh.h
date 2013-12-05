#ifndef MESH_H
#define MESH_H

#define VERTICES 0
#define COLORS 1

#include "GL\glew.h"
#include "GL\freeglut.h"
#include "glm\glm.hpp"

#include <Vector>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace glm;

class Mesh{

public:
	Mesh();
	void createBufferObject(std::vector<glm::vec4> &vertices);
	void draw(std::vector<glm::vec4> &vertices, GLuint _selectedProgram);

	void loadMesh(const char* fileName, std::vector<glm::vec4> & vertices);

private:
	GLuint VaoId[1], VboId[2];
	//int vao;//ibo;
	int size;
	
};
#endif
