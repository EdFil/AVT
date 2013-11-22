#include "Square.h"

Square::Square(){
	// Empty
}

void Square::createBufferObjects(GLuint* vaoId,GLuint* vboId){
	glBindVertexArray(vaoId[_vaoId]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[_vboId]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_vertexArray.size(), &_vertexArray[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(COLORS);
	glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertexArray[0].XYZW));
}

void Square::draw(GLuint uniformId, GLuint* vaoId) {
	glBindVertexArray(vaoId[_vaoId]);
	_current.lerp(_transformationMatrix[_matrixToUse]);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, _current.toArray());
	glDrawArrays(GL_TRIANGLES,0,_vertexArray.size());
}