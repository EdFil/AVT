#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "glm\glm.hpp"
#include <iostream>
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


	char* _name;
	TransformationOrder _order;
	GLuint _vaoId;
	GLuint _vboId;
	bool _selected;

	GLubyte _matrixToUse;

	int _currentTrans;
	std::vector<Vertex> _vertexArray;
	std::vector<vec3> _modifiedVertexArray;
	std::vector<mat4> _transformationMatrix;

public:

	Object();
	bool isOpenGLError();

    virtual void createBufferObjects(GLuint* vaoId, GLuint* vboId) = 0;
	virtual void draw(GLuint uniformId, GLuint* vaoId) = 0;
	
	Vertex* parseVertexInfo(char* objectName);

	virtual bool checkIntersection(vec3 rayOrigin, vec3 rayDir, vec3 &outputVec);
	void addTransformationMatrix();
	void removeTransformationMatrix();
	void nextTransformationMatrix();
	void prevTransformationMatrix();
	int getTransformationMatrixSize(){ return _transformationMatrix.size(); }
	int getMatrixToUse(){ return _matrixToUse; }

	void modifyVertexArray(mat4, mat4, mat4);

	inline const mat4 &getTransformationMatrix(GLubyte index) { return _transformationMatrix[index]; }
	virtual void toggleMatrix(const mat4 &viewMatrix, const mat4 &projMatrix) {
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
		updateModifiedVertex();
		
	}
	inline void setVaoId(GLuint vaoId) { _vaoId = vaoId; }
	inline void setVboId(GLuint vboId) { _vboId = vboId; }

	void translateMatrix(float x,float y,float z);
	void rotateMatrix(float,vec3);
	void updateModifiedVertex();

private:
	vec3 vertexToVec3(float[4]);
	void explode(std::string const & s, char delim, float* result);
};

#endif

