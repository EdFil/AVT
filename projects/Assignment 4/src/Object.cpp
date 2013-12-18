#include "Object.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/intersect.hpp>

using namespace glm;

const vec3 Object::DEFAULT_POSITION = vec3(0,0,0);
const quat Object::DEFAULT_ROTATION = quat();
const vec3 Object::DEFAULT_SCALE = vec3(1,1,1);

Object::Object(std::string name) : _currentPropertyIndex(0), _name(name), _selected(false){
	Properties initialProperty = { DEFAULT_POSITION, DEFAULT_ROTATION, DEFAULT_SCALE };
	_propertiesArray.push_back(initialProperty);
	calculateModelMatrix();
}

Object::Object(std::string name, glm::vec3 position) : _currentPropertyIndex(0), _name(name), _selected(false){
	Properties initialProperty = { position, DEFAULT_ROTATION, DEFAULT_SCALE };
	_propertiesArray.push_back(initialProperty);
	calculateModelMatrix();
}

void Object::createBufferObjects(GLuint* vaoId, GLuint* vboId){
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

void Object::draw(GLuint* vaoId) {
	int uniformId, colorId, textureId;
	if(_selected){
		_programsToUse[1]->bind();
		uniformId = _programsToUse[1]->getModelMatrixUniformId();
		colorId = _programsToUse[1]->getColorUniformId();
		textureId = _programsToUse[1]->getTextureUniformId();
	}
	else{
		_programsToUse[0]->bind();
		uniformId = _programsToUse[0]->getModelMatrixUniformId();
		colorId = _programsToUse[0]->getColorUniformId();
		textureId = _programsToUse[1]->getTextureUniformId();
	}
	glBindVertexArray(vaoId[_vaoId]);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
	glUniform4fv(colorId, 1, _color);
	glUniform1i(textureId, 0);
	TextureManager::Inst()->BindTexture(TextureManager::WOOD_TEXTURE);
	glDrawArrays(GL_TRIANGLES,0,_vertexArray.size());
	glUseProgram(0);
}

void Object::setShaderManager(ShaderManager *shaderManager){
	_shaderManager = shaderManager;
}

void Object::setPrograms(){
	_programsToUse.push_back(_shaderManager->getProgram(0));
	_programsToUse.push_back(_shaderManager->getProgram(1));
}

bool Object::checkIntersection(vec3 rayOrigin, vec3 rayDir, vec3 &outputVect){
	for(size_t i = 0; i + 3 <= _modifiedVertexArray.size(); i+=3){
		if(intersectLineTriangle(rayOrigin, rayDir, _modifiedVertexArray[i], _modifiedVertexArray[i+1], _modifiedVertexArray[i+2], outputVect)){
			return true;
		}
	}
	return false;
}

void Object::vertexToVec3(){
	for(size_t i = 0;i < _vertexArray.size(); i++)
		_modifiedVertexArray.push_back(glm::vec3(_vertexArray[i].XYZW[0], _vertexArray[i].XYZW[1], _vertexArray[i].XYZW[2]));
}

void Object::translate(float x, float y, float z){
	_propertiesArray[_currentPropertyIndex].position += vec3(x,y,z);
	calculateModelMatrix();
	updateModifiedVertex();
}

void Object::rotate(float value, vec3 axis){
	_propertiesArray[_currentPropertyIndex].rotation = angleAxis(value, axis) * _propertiesArray[_currentPropertyIndex].rotation;
	calculateModelMatrix();
	updateModifiedVertex();
}

void Object::scale(float x, float y, float z){
	_propertiesArray[_currentPropertyIndex].position = vec3(x,y,z);
	calculateModelMatrix();
	updateModifiedVertex();
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
	calculateModelMatrix();
	updateModifiedVertex();
}

void Object::nextProperty(){
	if(_currentPropertyIndex < (int)_propertiesArray.size() - 1)
		_currentPropertyIndex++;
	calculateModelMatrix();
	updateModifiedVertex();
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

void Object::updateModifiedVertex(){
	_modifiedVertexArray.clear();
	for (unsigned int i = 0; i < _vertexArray.size(); i++)
		_modifiedVertexArray.push_back(glm::vec3(_currentModelMatrix * glm::vec4(_vertexArray[i].XYZW[0], 
																				 _vertexArray[i].XYZW[1],
																				 _vertexArray[i].XYZW[2],
																				 _vertexArray[i].XYZW[3])));
}

glm::vec3 Object::getPosition() const {
	return _propertiesArray[_currentPropertyIndex].position;
}

glm::quat Object::getRotation() const {
	return _propertiesArray[_currentPropertyIndex].rotation;
}

glm::vec3 Object::getScale() const{
	return _propertiesArray[_currentPropertyIndex].scale;
}

std::string Object::getName() const{
	return _name;
}

int Object::getPropertiesArraySize() const {
	return _propertiesArray.size();
}

int Object::getCurrentPropertyIndex() const {
	return _currentPropertyIndex;
}

void Object::unselect(){
	_selected = false;
}

void Object::select(){
	_selected = true;
}

void Object::setColor(const float color[4]){
	memcpy(_color, color, sizeof(float)*4);
}

void Object::setColor(const float r, const float g, const float b, const float a){
	_color[0] = r;
	_color[1] = g;
	_color[2] = b;
	_color[3] = a;
}