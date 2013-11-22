#ifndef SQUARE_H
#define SQUARE_H

#include "Drawable.h"

class Square : public Drawable {

public:
	Square();

	void createBufferObjects(GLuint* vaoId,GLuint* vboId);
	void draw(GLuint uniformId, GLuint* vaoId);
};

#endif
