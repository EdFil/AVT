#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "glm\glm.hpp"
#include <Vector>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "glm\gtx\intersect.hpp"

#define VERTICES 0
#define COLORS 1

using namespace glm;

class Object {

protected:
	typedef struct {
		float XYZW[4];
		float RGBA[4];
	} Vertex;

	enum TransformationOrder{
        UP,
        DOWN
    };

	TransformationOrder _order;
	GLuint _vaoId;
	GLuint _vboId;
	bool _selected;

	GLubyte _matrixToUse;

	int _currentTrans;
	std::vector<Vertex> _vertexArray;
	std::vector<Vertex> _modifiedVertexArray;
	std::vector<mat4> _transformationMatrix;

public:

	Object();
	bool isOpenGLError();

    virtual void createBufferObjects(GLuint* vaoId, GLuint* vboId) = 0;
	virtual void draw(GLuint uniformId, GLuint* vaoId) = 0;
	
	Vertex* parseVertexInfo(char* objectName);

	bool checkIntersection(vec3 rayOrigin, vec3 rayDir);

	void modifyVertexArray(mat4, mat4, mat4);

	inline const mat4 &getTransformationMatrix(GLubyte index) { return _transformationMatrix[index]; }
	virtual void toggleMatrix() {
		if(_order == TransformationOrder::UP){
			_matrixToUse++;
			if(_matrixToUse >= _transformationMatrix.size() - 1){
				_matrixToUse = _transformationMatrix.size() - 1;
				_order = TransformationOrder::DOWN;
			}
		}
		else if(_order == TransformationOrder::DOWN){
			_matrixToUse--;
			if(_matrixToUse <= 0){
				_matrixToUse = 0;
				_order = TransformationOrder::UP;
			}
		}
	}
	inline void setVaoId(GLuint vaoId) { _vaoId = vaoId; }
	inline void setVboId(GLuint vboId) { _vboId = vboId; }

private:
	vec3 vertexToVec3(float[4]);
	void explode(std::string const & s, char delim, float* result);
};

#endif

