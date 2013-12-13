#include "Line.h"
#include <glm/gtc/type_ptr.hpp>
using namespace glm;


const float Line::LINE_WIDTH = 0.01f;
const float Line::LINE_LENGTH = 10.0f;

Line::Line() : Object("Axis Line"), _isVisible(false), _axis(glm::vec3(0,0,0)){
	Vertex bottomBackLeft = { {-LINE_WIDTH, -LINE_WIDTH,  -LINE_LENGTH, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	Vertex bottomBackRight= { { LINE_WIDTH, -LINE_WIDTH,  -LINE_LENGTH, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	Vertex bottomTopLeft  = { {-LINE_WIDTH, -LINE_WIDTH,   LINE_LENGTH, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	Vertex bottomTopRight = { { LINE_WIDTH, -LINE_WIDTH,   LINE_LENGTH, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	Vertex topBackLeft    = { {-LINE_WIDTH,  LINE_WIDTH,  -LINE_LENGTH, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	Vertex topBackRight   = { { LINE_WIDTH,  LINE_WIDTH,  -LINE_LENGTH, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	Vertex topTopLeft     = { {-LINE_WIDTH,  LINE_WIDTH,   LINE_LENGTH, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	Vertex topTopRight    = { { LINE_WIDTH,  LINE_WIDTH,   LINE_LENGTH, 1.0f}, {1.0, 1.0f, 1.0f, 1.0f} };
	//Bottom
	_vertexArray.push_back(bottomBackLeft);
	_vertexArray.push_back(bottomTopRight);
	_vertexArray.push_back(bottomTopLeft);
	_vertexArray.push_back(bottomTopRight);
	_vertexArray.push_back(bottomBackLeft);
	_vertexArray.push_back(bottomBackRight);
	//Top
	_vertexArray.push_back(topTopRight);
	_vertexArray.push_back(topBackLeft);
	_vertexArray.push_back(topTopLeft);
	_vertexArray.push_back(topBackLeft);
	_vertexArray.push_back(topTopRight);
	_vertexArray.push_back(topBackRight);
	//Left
	_vertexArray.push_back(topBackLeft);
	_vertexArray.push_back(bottomBackLeft);
	_vertexArray.push_back(bottomTopLeft);
	_vertexArray.push_back(topTopLeft);
	_vertexArray.push_back(topBackLeft);
	_vertexArray.push_back(bottomTopLeft);
	//Right
	_vertexArray.push_back(bottomBackRight);
	_vertexArray.push_back(topBackRight);
	_vertexArray.push_back(bottomTopRight);
	_vertexArray.push_back(topBackRight);
	_vertexArray.push_back(topTopRight);
	_vertexArray.push_back(bottomTopRight);
}

void Line::bindToObject(Object* obj){
	_object = obj;
}

void Line::setToAxis(glm::vec3 axis){
	_axis = axis;
	if(axis.x == 1)
		_propertiesArray[_currentPropertyIndex].rotation = angleAxis(90.0f, glm::vec3(0,1,0));
	else if(axis.y == 1)
		_propertiesArray[_currentPropertyIndex].rotation = angleAxis(90.0f, glm::vec3(1,0,0));
	else if(axis.z == 1)
		_propertiesArray[_currentPropertyIndex].rotation = quat();
}

void Line::setVisible(bool value){
	_isVisible = value;
	if(_isVisible == false)
		_axis = glm::vec3(0,0,0);
}

bool Line::checkIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec3 &outputVec){
	return false;
}

void Line::updateModifiedVertex(){}

void Line::draw(GLuint* vaoId) {
	if(_isVisible && (_object != NULL) && _axis != glm::vec3(0,0,0)){
		_propertiesArray[_currentPropertyIndex].position = _object->getPosition();
		calculateModelMatrix();
		_programsToUse[0]->bind();
		glBindVertexArray(vaoId[_vaoId]);
		glUniformMatrix4fv(_programsToUse[0]->getUniformId(), 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
		glDrawArrays(GL_TRIANGLES,0,_vertexArray.size());
	}
}
