#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Drawable.h"

class Triangle : public Drawable {

public:
	static GLuint _savedVboIndex;
	
	Triangle();

	void createBufferObjects(GLuint* vaoId,GLuint* vboId);
	void draw(GLuint uniformId, GLuint* vaoId);
	bool setVboIndexId(GLuint vboIndexId);
};

#endif
