#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>

#include "Drawable.h"

class ObjectManager {
	
	/* A List where all objects are stored */
	std::vector<Drawable*> _objectList;

	GLuint* _vaoId;
	GLuint* _vboId;

	GLuint _vaoCounter;
	GLuint _vboCounter;

	/* The Uniform ID value */
	GLint _uniformId;

public:

	ObjectManager::ObjectManager(GLint uniformId);
	/* Add a drawable object to the list */
	void addObject(Drawable* object);

	/* Create buffers for all objects */
	void createBufferObjects();

	void destroyBufferObjects();
	/* Draw all objects */
	void drawObjects();

	void changeTri(GLubyte index){
		for(unsigned int i = 0; i < _objectList.size(); i++)
			_objectList[i]->setMatrixToUse(index);
	}

private:

	GLuint getNewVaoId();
	GLuint getNewVboId();

};



#endif
