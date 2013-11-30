#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>

#include "Object.h"
#include "Camera.h"

class ObjectManager {
	
	enum TransformationOrder{
        UP,
        DOWN
    };

	/* A List where all objects are stored */
	std::vector<Object*> _objectList;

	GLuint _goIndex;
	TransformationOrder _order;

	GLuint* _vaoId;
	GLuint* _vboId;

	GLuint _selectedProgram;
	GLuint _selectedUniform;

	GLuint _vaoCounter;
	GLuint _vboCounter;

	/* The Uniform ID value */
	GLint _uniformBlockId;
	GLuint UBO_BP;

public:

	ObjectManager();
	ObjectManager::ObjectManager(GLuint uniformId, GLuint selectedProgram);
	/* Add a drawable object to the list */
	void addObject(Object* object);

	/* Create buffers for all objects */
	void createBufferObjects();

	void destroyBufferObjects();
	/* Draw all objects */
	void drawObjects(const glm::mat4& viewMatrix, const glm::mat4& projMatrix);

	void changeTri(){
		if(_order == TransformationOrder::UP)
			_objectList[_goIndex++]->toggleMatrix();
		else if(_order == TransformationOrder::DOWN)
			_objectList[_goIndex--]->toggleMatrix();
		if(_goIndex >= _objectList.size()){
			_order = TransformationOrder::DOWN;
			_goIndex = _objectList.size() - 1;
		}
		else if (_goIndex < 1){
			_order = TransformationOrder::UP;
			_goIndex = 1;
		}
	}

	inline void setSelectedUniform(GLuint id) { _selectedUniform = id; }
	inline void setSelectedProgram(GLuint id) { _selectedProgram = id; }

private:
	GLuint getNewVaoId();
	GLuint getNewVboId();

};



#endif
