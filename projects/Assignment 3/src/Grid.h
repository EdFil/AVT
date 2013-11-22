#ifndef GRID_H
#define GRID_H

#include "Drawable.h"

class Grid : public Drawable {

public:
	Grid(int, float);

	void createBufferObjects(GLuint* vaoId,GLuint* vboId);
	void draw(GLuint uniformId, GLuint* vaoId);

private:

	void addVertex(float, float);
};

#endif
