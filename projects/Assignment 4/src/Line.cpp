#include "Line.h"
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <iostream>
#include <sstream>
#include <string>

Line::Line(vec4 orig, vec4 dest){
	_transformationMatrix.push_back(mat4());
	_transformationMatrix.push_back(mat4());
	Vertex mOrig = {{orig.x, orig.y, orig.z, orig.w}, {1.0f, 1.0f, 1.0f, 1.0f}};
	Vertex mDest = {{dest.x, dest.y, dest.z, dest.w}, {1.0f, 1.0f, 1.0f, 1.0f}};
	_vertexArray.push_back(mOrig);
	_vertexArray.push_back(mDest);
}

void Line::newLine(vec4 orig, vec4 dest){
	std::cout << "Orig: [" << orig.x << ", " << orig.y << ", " << orig.z << ", " << orig.w << "]" << std::endl <<
				 "Dest: [" << dest.x << ", " << dest.y << ", " << dest.z << ", " << dest.w << "]" << std::endl;
	_vertexArray = std::vector<Vertex>();
	Vertex mOrig = {{orig.x, orig.y, orig.z, orig.w}, {1.0f, 0.0f, 0.0f, 1.0f}};
	Vertex mDest = {{dest.x, dest.y, dest.z, dest.w}, {1.0f, 1.0f, 1.0f, 1.0f}};
	_vertexArray.push_back(mOrig);
	_vertexArray.push_back(mDest);
}

void Line::createBufferObjects(GLuint* vaoId,GLuint* vboId){
	glBindVertexArray(vaoId[_vaoId]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[_vboId]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_vertexArray.size(), &_vertexArray[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(COLORS);
	glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertexArray[0].XYZW));
}

void Line::draw(GLuint uniformId, GLuint* vaoId) {
	glBindVertexArray(vaoId[_vaoId]);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(getTransformationMatrix(0)));
	glDrawArrays(GL_LINES,0,_vertexArray.size());
}

void Line::toggleMatrix(){
	//Empty
}

void Line::checkIntersection(){
	//Empty
}