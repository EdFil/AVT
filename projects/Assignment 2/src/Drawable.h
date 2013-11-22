#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <iostream>
#include "rapidxml.hpp"
#include "Matrix.h"
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
	GLuint _vboVertexId;
	GLuint _vboIndexId;

	GLubyte _matrixToUse;

	Matrix* _current;
	std::vector<Vertex> _vertexArray;
	std::vector<GLubyte> _indexArray;
	std::vector<Matrix> _transformationMatrix;

public:

	Drawable();
	bool isOpenGLError();

    virtual void createBufferObjects(GLuint* vaoId, GLuint* vboId) = 0;
	virtual void draw(GLuint uniformId, GLuint* vaoId) = 0;
	
	Vertex* parseVertexInfo(char* objectName);

	inline Matrix* getTransformationMatrix(GLubyte index) { return &_transformationMatrix[index]; }
	inline void setMatrixToUse(GLubyte index) { _matrixToUse = index; }
	inline void setVaoId(GLuint vaoId) { _vaoId = vaoId; }
	inline void setVboVertexId(GLuint vboVertexId) { _vboVertexId = vboVertexId; }
	inline virtual bool setVboIndexId(GLuint vboIndexId) { _vboIndexId = vboIndexId; return true; }

private:
	void explode(std::string const & s, char delim, float* result);
};

#endif
