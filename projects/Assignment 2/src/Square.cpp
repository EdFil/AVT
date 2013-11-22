#include "Square.h"

GLuint Square::_savedVboIndex = 0;

Square::Square(){
	// { 0, 1, 2, 3 }
	for(int i = 0; i < 4; i++)
		_indexArray.push_back(i);
}

void Square::createBufferObjects(GLuint* vaoId,GLuint* vboId){
	glBindVertexArray(vaoId[_vaoId]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[_vboVertexId]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*4, &_vertexArray[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(COLORS);
	glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertexArray[0].XYZW));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[_vboIndexId]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*4, &_indexArray[0], GL_STATIC_DRAW);
}

void Square::draw(GLuint uniformId, GLuint* vaoId) {
	glBindVertexArray(vaoId[_vaoId]);
	_current->lerp(getTransformationMatrix(_matrixToUse));
	glUniformMatrix4fv(uniformId, 1, GL_TRUE, _current->toArray());
	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);
}

bool Square::setVboIndexId(GLuint vboIndexId){ 
	if(_savedVboIndex == 0){
		_vboIndexId = vboIndexId;
		return true;
	}
	_vboIndexId = _savedVboIndex;
	return false;
}