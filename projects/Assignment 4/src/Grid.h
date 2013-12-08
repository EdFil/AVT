#ifndef GRID_H
#define GRID_H

#include "Object.h"

class Grid : public Object {

public:
	Grid(int, float);

	//Virtual functions
	void draw(GLuint uniformId, GLuint* vaoId);

	//Moving functions
	bool checkIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec3 &outputVec);

private:

	void addVertex(float, float);
};

#endif
