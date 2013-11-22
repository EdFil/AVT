#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <iostream>
#include <Vector>
#include "rapidxml.hpp"
#include "Matrix4.h"
#include "GL\glew.h"
#include "GL\freeglut.h"

#define VERTICES 0
#define COLORS 1

class Drawable {

protected:
	typedef struct {
		GLfloat XYZW[4];
		GLfloat RGBA[4];
	} Vertex;

	GLuint _vaoId;
	GLuint _vboId;
	bool _selected;

	GLubyte _matrixToUse;

	Matrix4 _current;

	std::vector<Vertex> _vertexArray;
	std::vector<Matrix4> _transformationMatrix;

public:

	Drawable();
	bool isOpenGLError();

    virtual void createBufferObjects(GLuint* vaoId, GLuint* vboId) = 0;
	virtual void draw(GLuint uniformId, GLuint* vaoId) = 0;
	
	Vertex* parseVertexInfo(char* objectName);

	inline Matrix4* getTransformationMatrix(GLubyte index) { return &_transformationMatrix[index]; }
	inline void toggleMatrix() {
		if(_selected)
			_matrixToUse = 1;
		else
			_matrixToUse = 0;
		_selected = !_selected;
	}
	inline void setVaoId(GLuint vaoId) { _vaoId = vaoId; }
	inline void setVboId(GLuint vboId) { _vboId = vboId; }

private:
	void explode(std::string const & s, char delim, float* result);
};

#endif
