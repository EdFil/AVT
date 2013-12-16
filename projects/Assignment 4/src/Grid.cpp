#include "Grid.h"
#include <glm/gtc/type_ptr.hpp>

Grid::Grid(int x, float inc) : Object("Grid"){
	for(float i = (float) -x; i <= x; i += inc){
		addVertex(i, (float)-x);
		addVertex(i, (float) x);
		addVertex((float)-x, i);
		addVertex((float) x, i);
	}
}

void Grid::addVertex(float x, float z){
	Vertex vertex = { {x, 0.0f, z, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	_vertexArray.push_back(vertex);
}

bool Grid::checkIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec3 &outputVec){
	return false;
}

void Grid::updateModifiedVertex(){}

void Grid::draw(GLuint* vaoId) {
	_programsToUse[0]->bind();
	glBindVertexArray(vaoId[_vaoId]);
	glUniformMatrix4fv(_programsToUse[0]->getModelMatrixUniformId(), 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
	glDrawArrays(GL_LINES,0,_vertexArray.size());
}