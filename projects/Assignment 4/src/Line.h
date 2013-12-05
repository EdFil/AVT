#ifndef LINE_H
#define LINE_H

#include "Object.h"

class Line : public Object {

public:
	Line(glm::vec4 orig, glm::vec4 dest);

	void newLine(glm::vec4 orig, glm::vec4 dest);
	void createBufferObjects(GLuint* vaoId,GLuint* vboId);
	void draw(GLuint uniformId, GLuint* vaoId);
	void toggleMatrix();
	void checkIntersection();
};

#endif
