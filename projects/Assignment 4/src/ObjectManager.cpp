#include "ObjectManager.h"
#include <glm/gtc/type_ptr.hpp>

ObjectManager::ObjectManager(){}

ObjectManager::ObjectManager(GLuint uniformId, GLuint selectedProgram) :  _vaoCounter(0), _vboCounter(0), UBO_BP(0){
	_selectedProgram = selectedProgram;
	_selectedUniform = uniformId;
	_uniformBlockId = _vboCounter++;
}

void ObjectManager::addObject(Object* object){
	//Set a number of variables for the buffers
	object->setVaoId(_vaoCounter++);
	object->setVboId(_vboCounter++);

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

/*void ObjectManager::createBufferObjects2(std::vector<glm::vec4> &vertices){
	_vaoId = new GLuint[_vaoCounter];
	_vboId = new GLuint[_vboCounter];

	glGenVertexArrays(_vaoCounter, _vaoId);	//Vertex Array
	glGenBuffers(_vboCounter, _vboId);		//Buffer Array


	// Create all buffers for objects
	for (unsigned int i = 0; i < _objectList.size(); i++)
		_objectList[i]->createBufferObjects2(_vaoId, _vboId, vertices);

	//Reserve space for the Uniform Blocks
	//glBindBuffer(GL_ARRAY_BUFFER, _vboId[0]);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec4), &vertices[0], GL_STATIC_DRAW);

	// Clear buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
}*/

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

	glUseProgram(_selectedProgram);

	for(unsigned int i = 0; i < _objectList.size(); i++)
		_objectList[i]->draw(_selectedUniform, _vaoId);

	glUseProgram(0);
	glBindVertexArray(0);
}

/*void ObjectManager::drawObjects2(const glm::mat4 &viewMatrix, const glm::mat4 &projMatrix, std::vector<glm::vec4> &vertices){
	glBindBuffer(GL_ARRAY_BUFFER, _vboId[_uniformBlockId]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 16, glm::value_ptr(viewMatrix));
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 16, sizeof(float) * 16, glm::value_ptr(projMatrix));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(_selectedProgram);

	for (unsigned int i = 0; i < _objectList.size(); i++)
		_objectList[i]->draw(_selectedUniform, _vaoId);

	glUseProgram(0);
	glBindVertexArray(0);
}*/