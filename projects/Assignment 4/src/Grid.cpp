#include "Grid.h"
#include <glm/gtc/type_ptr.hpp>

Grid::Grid(int x, float inc) : Object("Grid"){
	for(float i = (float) -x; i <= x; i += inc){
		addVertex(i, (float)-x);
		addVertex(i, (float) x);
		addVertex((float)-x, i);
		addVertex((float) x, i);
	}
	setColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void Grid::setPrograms(){
	_programsToUse.push_back(_shaderManager->getProgram("SimpleShader"));
}

void Grid::addVertex(float x, float z){
	Vertex vertex = {{x, 0.0f, z, 1.0f}};
	_vertexArray.push_back(vertex);
}

bool Grid::checkIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec3 &outputVec){
	return false;
}


void Grid::updateModifiedVertex(){}

void Grid::createBufferObjects(GLuint* vaoId, GLuint* vboId){
	glBindVertexArray(vaoId[_vaoId]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[_vboId]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_vertexArray.size(), &_vertexArray[0], GL_STATIC_DRAW);
	//Vertex Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//Vertex Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertexArray[0].XYZW));
	//Vertex UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(_vertexArray[0].NORMAL)*2));
}

void Grid::draw(GLuint* vaoId) {
	SimpleProgram* program = (SimpleProgram*)_programsToUse[0];
	program->bind();
	glBindVertexArray(vaoId[_vaoId]);
	glUniformMatrix4fv(program->getModelMatrixUniformId(), 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
	glUniform4fv(program->getColorUniformId(), 1, _color);
	glDrawArrays(GL_LINES,0,_vertexArray.size());
}

void Grid::saveObject(std::string filename){}