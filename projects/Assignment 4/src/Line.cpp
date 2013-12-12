#include "Line.h"
#include <glm/gtc/type_ptr.hpp>
using namespace glm;


Line::Line() : Object("Axis Line"), _isVisible(false){
	Vertex vertex1 = { {0.0f, 0.0f, -10.0f, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	Vertex vertex2 = { {0.0f, 0.0f,  10.0f, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	_vertexArray.push_back(vertex1);
	_vertexArray.push_back(vertex2);
}

void Line::bindToObject(Object* obj){
	_object = obj;
}

void Line::setToAxis(glm::vec3 axis){
	if(axis.x == 1)
		_propertiesArray[0].rotation = angleAxis(90.0f, glm::vec3(0,1,0));
	else if(axis.y == 1)
		_propertiesArray[0].rotation = angleAxis(90.0f, glm::vec3(1,0,0));
	else if(axis.z == 1)
		_propertiesArray[0].rotation = quat();
}

void Line::setVisible(bool value){
	_isVisible = value;
}

bool Line::checkIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec3 &outputVec){
	return false;
}

void Line::updateModifiedVertex(){}

void Line::draw(GLuint* vaoId) {
	if(_isVisible && (_object != NULL)){
		_propertiesArray[0].position = _object->getPosition();
		calculateModelMatrix();
		_programsToUse[0]->bind();
		glBindVertexArray(vaoId[_vaoId]);
		glUniformMatrix4fv(_programsToUse[0]->getUniformId(), 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
		glDrawArrays(GL_LINES,0,_vertexArray.size());
	}
}
