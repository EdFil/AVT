#ifndef GRID_H
#define GRID_H

#include "Object.h"

class Grid : public Object {

public:
	Grid(int, float);

	void createBufferObjects(GLuint* vaoId,GLuint* vboId);
	void draw(GLuint uniformId, GLuint* vaoId);
	void toggleMatrix();
	bool checkIntersection(vec3 rayOrigin, vec3 rayDir, vec3 &outputVec);

private:

	void addVertex(float, float);
};

#endif
