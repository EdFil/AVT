#include "Grid.h"
#include <glm/gtc/type_ptr.hpp>

Grid::Grid(int x, float inc){
	_transformationMatrix.push_back(mat4());
	_transformationMatrix.push_back(mat4());
	for(float i = (float) -x; i <= x; i += inc){
		addVertex(i, (float)-x);
		addVertex(i, (float) x);
		addVertex((float)-x, i);
		addVertex((float) x, i);
	}
}

void Grid::createBufferObjects(GLuint* vaoId,GLuint* vboId){
	glBindVertexArray(vaoId[_vaoId]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[_vboId]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_vertexArray.size(), &_vertexArray[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(COLORS);
	glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertexArray[0].XYZW));
}

void Grid::draw(GLuint uniformId, GLuint* vaoId) {
	glBindVertexArray(vaoId[_vaoId]);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(getTransformationMatrix(0)));
	glDrawArrays(GL_LINES,0,_vertexArray.size());
}

void Grid::addVertex(float x, float z){
	Vertex vertex = { {x, 0.0f, z, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	_vertexArray.push_back(vertex);
}

void Grid::toggleMatrix(){
	//Empty
}