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

	//Buffer functions
	void createBufferObjects();
	void createBufferObjects(int index);
	void destroyBufferObjects();

	//Animation Functions
	void addAnimationFrame();
	void removeAnimationFrame();
	void nextAnimationFrame();
	void prevAnimationFrame();

	
	/* Draw all objects */
	void drawObjects(const glm::mat4& viewMatrix, const glm::mat4& projMatrix);

	Object* checkIntersection(vec3 rayOrigin, vec3 rayDir);

	inline void setSelectedUniform(GLuint id) { _selectedUniform = id; }
	inline void setSelectedProgram(GLuint id) { _selectedProgram = id; }

private:
	GLuint getNewVaoId();
	GLuint getNewVboId();

};



#endif
