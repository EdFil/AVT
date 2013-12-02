#ifndef GRID_H
#define GRID_H

#include "Object.h"

class Grid : public Object {

public:
	Grid(int, float);

	void createBufferObjects(GLuint* vaoId,GLuint* vboId);
	void draw(GLuint uniformId, GLuint* vaoId);
	void toggleMatrix();

private:

	void addVertex(float, float);
};

#endif
