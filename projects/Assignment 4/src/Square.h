#ifndef SQUARE_H
#define SQUARE_H

#include "Object.h"

class Square : public Object {

public:
	Square();

	void createBufferObjects(GLuint* vaoId,GLuint* vboId);
	void draw(GLuint uniformId, GLuint* vaoId);
};

#endif
