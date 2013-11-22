#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Drawable.h"

class Triangle : public Drawable {

public:
	Triangle();

	bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

	void createBufferObjects(GLuint* vaoId,GLuint* vboId);
	void draw(GLuint uniformId, GLuint* vaoId);
};

#endif
