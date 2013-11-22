#ifndef SQUARE_H
#define SQUARE_H

#include "Drawable.h"

class Square : public Drawable {

public:
	static GLuint _savedVboIndex;
	
	Square();

	void createBufferObjects(GLuint* vaoId,GLuint* vboId);
	void draw(GLuint uniformId, GLuint* vaoId);
	bool setVboIndexId(GLuint vboIndexId);
};

#endif
