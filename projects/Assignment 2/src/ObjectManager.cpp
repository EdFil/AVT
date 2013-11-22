#include "ObjectManager.h"

ObjectManager::ObjectManager(GLint uniformId) : _uniformId(uniformId), _vaoCounter(0), _vboCounter(0){
	//Empty
}

void ObjectManager::addObject(Drawable* object){
	//Set a number of variables for the buffers
	object->setVaoId(_vaoCounter++);
	object->setVboVertexId(_vboCounter++);
	if(object->setVboIndexId(_vboCounter))
		_vboCounter++;

	//Add the Object to The object list
	_objectList.push_back(object);
}

void ObjectManager::createBufferObjects(){
	_vaoId = new GLuint[_vaoCounter];
	_vboId = new GLuint[_vboCounter];
	glGenVertexArrays(_vaoCounter, _vaoId);	//Vertex Array
	glGenBuffers(_vboCounter, _vboId);		//Buffer Array

	// Create all buffers for objects
	for(unsigned int i = 0; i < _objectList.size(); i++)
		_objectList[i]->createBufferObjects(_vaoId, _vboId);

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

void ObjectManager::drawObjects(){ 
		for(unsigned int i = 0; i < _objectList.size(); i++)
			_objectList[i]->draw(_uniformId, _vaoId);
	}
