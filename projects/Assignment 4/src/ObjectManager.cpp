#include "ObjectManager.h"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"

ObjectManager::ObjectManager(){}

ObjectManager::ObjectManager(ShaderManager *shaderManager) :  _vaoCounter(0), _vboCounter(0), UBO_BP(0), _animationCounter(1), _currentAnimation(0){
	_uniformBlockId = _vboCounter++;
	_shaderManager = shaderManager;
}


Object* ObjectManager::checkIntersection(vec3 rayOrigin, vec3 rayEnd){
	Object *returnObject = NULL;
	vec3 interceptVector(100,100,100), aux;
	for(unsigned int i = 0; i < _objectList.size(); i++){
		if(_objectList[i]->checkIntersection(rayOrigin, rayEnd, aux)){
			if(length(aux - rayOrigin) < length(interceptVector - rayOrigin)){
				interceptVector = aux;
				returnObject = _objectList[i];
			}
		}
	}
	return returnObject;
}

void ObjectManager::updateModifiedVertexArray(){
	for(unsigned int i = 0; i < _objectList.size(); i++)
		_objectList[i]->updateModifiedVertex();
}

void ObjectManager::addObject(Object* object){
	//Set a number of variables for the buffers
	object->setVaoId(_vaoCounter++);
	object->setVboId(_vboCounter++);
	object->setShaderManager(_shaderManager);
	object->setPrograms();

	//Add the Object to The object list
	_objectList.push_back(object);
}

void ObjectManager::createBufferObjects(int index){
	_objectList[index]->createBufferObjects(_vaoId, _vboId);
}

void ObjectManager::addAnimationFrame(){
	for(size_t i = 0; i < _objectList.size(); i++)
		_objectList[i]->addProperty();
	printf("Added new animation frame.\nCurrently on fram %d out of %d\n", _objectList[0]->getCurrentPropertyIndex()+1, _objectList[0]->getPropertiesArraySize());
}

void ObjectManager::removeAnimationFrame(){
	for(size_t i = 0; i < _objectList.size(); i++)
		_objectList[i]->removeProperty();
		printf("Removed animation frame.\nCurrently on fram %d out of %d\n", _objectList[0]->getCurrentPropertyIndex()+1, _objectList[0]->getPropertiesArraySize());
}

void ObjectManager::nextAnimationFrame(){
	for(size_t i = 0; i < _objectList.size(); i++)
		_objectList[i]->nextProperty();
	printf("Currently on frame %d out of %d.\n", _objectList[0]->getCurrentPropertyIndex()+1, _objectList[0]->getPropertiesArraySize());
}

void ObjectManager::prevAnimationFrame(){
	for(size_t i = 0; i < _objectList.size(); i++)
		_objectList[i]->prevProperty();
	printf("Currently on frame %d out of %d.\n", _objectList[0]->getCurrentPropertyIndex()+1, _objectList[0]->getPropertiesArraySize());
}


void ObjectManager::createBufferObjects(){
	_vaoId = new GLuint[_vaoCounter];
	_vboId = new GLuint[_vboCounter];

	glGenVertexArrays(_vaoCounter, _vaoId);	//Vertex Array
	glGenBuffers(_vboCounter, _vboId);		//Buffer Array

	// Create all buffers for objects
	for(unsigned int i = 0; i < _objectList.size(); i++)
		_objectList[i]->createBufferObjects(_vaoId, _vboId);

	//Reserve space for the Uniform Blocks
	glBindBuffer(GL_UNIFORM_BUFFER, _vboId[_uniformBlockId]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(float)*16*2, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _vboId[_uniformBlockId]);

	// Clear buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
}

void ObjectManager::destroyBufferObjects(){
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(_vboCounter, _vboId);
	glDeleteVertexArrays(_vaoCounter, _vboId);
}

void ObjectManager::drawObjects(const glm::mat4 &viewMatrix, const glm::mat4 &projMatrix){ 
	glBindBuffer(GL_UNIFORM_BUFFER, _vboId[_uniformBlockId]);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float)*16, glm::value_ptr(viewMatrix));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float)*16, sizeof(float)*16, glm::value_ptr(projMatrix));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	for(unsigned int i = 0; i < _objectList.size(); i++)
		_objectList[i]->draw(_vaoId);

	glUseProgram(0);
	glBindVertexArray(0);
}
