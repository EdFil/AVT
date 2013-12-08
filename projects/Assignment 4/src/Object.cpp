#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/intersect.hpp>

using namespace glm;

const vec3 Object::DEFAULT_POSITION = vec3(0,0,0);
const quat Object::DEFAULT_ROTATION = quat();
const vec3 Object::DEFAULT_SCALE = vec3(1,1,1);

Object::Object(char* name) : _currentPropertyIndex(0), _name(name), _selected(false){
	Properties initialProperty = { DEFAULT_POSITION, DEFAULT_ROTATION, DEFAULT_SCALE };
	_propertiesArray.push_back(initialProperty);
	calculateModelMatrix();
}

void Object::createBufferObjects(GLuint* vaoId, GLuint* vboId){
	glBindVertexArray(vaoId[_vaoId]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[_vboId]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_vertexArray.size(), &_vertexArray[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(COLORS);
	glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertexArray[0].XYZW));
}

void Object::draw(GLuint uniformId, GLuint* vaoId) {
	glBindVertexArray(vaoId[_vaoId]);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
	glDrawArrays(GL_TRIANGLES,0,_vertexArray.size());
}

bool Object::checkIntersection(vec3 rayOrigin, vec3 rayDir, vec3 &outputVect){
	for(size_t i = 0; i + 3 <= _vertexArray.size(); i+=3){
		if(intersectLineTriangle(rayOrigin, rayDir, vertexToVec3(_vertexArray[i]), vertexToVec3(_vertexArray[i+1]), vertexToVec3(_vertexArray[i+2]), outputVect)){
			return true;
		}
	}
	return false;
}

glm::vec3 Object::vertexToVec3(const Vertex &vertex){
	return glm::vec3(vertex.XYZW[0], vertex.XYZW[1], vertex.XYZW[2]); 
}

void Object::translate(float x, float y, float z){
	_propertiesArray[_currentPropertyIndex].position += vec3(x,y,z);
	calculateModelMatrix();
}

void Object::rotate(float value, vec3 axis){
	_propertiesArray[_currentPropertyIndex].rotation = _propertiesArray[_currentPropertyIndex].rotation * angleAxis(value, axis);
	calculateModelMatrix();
}

void Object::scale(float x, float y, float z){
	_propertiesArray[_currentPropertyIndex].position = vec3(x,y,z);
	calculateModelMatrix();
}

void Object::addProperty(){
	_propertiesArray.insert(_propertiesArray.begin() + _currentPropertyIndex, _propertiesArray[_currentPropertyIndex]);
	_currentPropertyIndex++;
}

void Object::removeProperty(){
	if(_propertiesArray.size() != 1){
		_propertiesArray.erase(_propertiesArray.begin() + _currentPropertyIndex);
		if(_currentPropertyIndex > 0)
			_currentPropertyIndex--;
	}
}
void Object::prevProperty(){
	if(_currentPropertyIndex > 0)
		_currentPropertyIndex--;
}

void Object::nextProperty(){
	if(_currentPropertyIndex < (int)_propertiesArray.size() - 1)
		_currentPropertyIndex++;
}

void Object::calculateModelMatrix(){
	mat4 transformation1 = glm::scale(_propertiesArray[_currentPropertyIndex].scale);
	mat4 transformation2 = glm::toMat4(_propertiesArray[_currentPropertyIndex].rotation);
	mat4 transformation3 = glm::translate(_propertiesArray[_currentPropertyIndex].position);
	_currentModelMatrix = transformation3 * transformation2 * transformation1 * mat4();
}

void Object::setVaoId(int value){
	_vaoId = value;
}

void Object::setVboId(int value){
	_vboId = value;
}