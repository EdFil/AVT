#include "Triangle.h"

GLuint Triangle::_savedVboIndex = 0;

Triangle::Triangle(){
	// { 0, 1, 2 }
	for(int i = 0; i < 3; i++)
		_indexArray.push_back(i);
}

void Triangle::createBufferObjects(GLuint* vaoId,GLuint* vboId){
	glBindVertexArray(vaoId[_vaoId]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[_vboVertexId]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*3, &_vertexArray[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(COLORS);
	glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertexArray[0].XYZW));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[_vboIndexId]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*3, &_indexArray[0], GL_STATIC_DRAW);
}

void Triangle::draw(GLuint uniformId, GLuint* vaoId) {
	glBindVertexArray(vaoId[_vaoId]);
	_current->lerp(getTransformationMatrix(_matrixToUse));
	glUniformMatrix4fv(uniformId, 1, GL_TRUE, _current->toArray());
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);
}

bool Triangle::setVboIndexId(GLuint vboIndexId){ 
	if(_savedVboIndex == 0){
		_vboIndexId = vboIndexId;
		return true;
	}
	_vboIndexId = _savedVboIndex;
	return false;
}