#ifndef GRID_H
#define GRID_H

#include "Object.h"

class Grid : public Object {

public:
	Grid(int, float);

	//Virtual functions
	void draw(GLuint* vaoId);
	bool checkIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec3 &outputVec);
	void updateModifiedVertex();
	void setPrograms();
	void saveObject(std::string);
	void createBufferObjects(GLuint*, GLuint*);

private:

	void addVertex(float, float);
};

#endif
