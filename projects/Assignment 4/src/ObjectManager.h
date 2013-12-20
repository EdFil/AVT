#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>

#include "Object.h"
#include "Camera.h"
#include "ButtonObject.h"

class ObjectManager {
	
	enum TransformationOrder{
        UP,
        DOWN
    };

	/* A List where all objects are stored */
	std::vector<Object*> _objectList;
	std::vector<ButtonObject*> _buttonObjectList;
	ShaderManager *_shaderManager;

	GLuint _goIndex;
	TransformationOrder _order;

	int _elapsedTime;
	int _timeToSwitchFrame;

	GLuint* _vaoId;
	GLuint* _vboId;

	GLuint _vaoCounter;
	GLuint _vboCounter;
	int _animationCounter;
	int _currentAnimation;

	/* The Uniform ID value */
	GLint _uniformBlockId;
	GLuint UBO_BP;

public:

	ObjectManager();
	ObjectManager(ShaderManager *shaderManager);
	/* Add a drawable object to the list */
	void addButtonObject(ButtonObject*);
	void addObject(Object* object);
	void removeObjects();

	void saveObjects(std::string);
	void loadObjects(std::string);

	//Buffer functions
	void createBufferObjects();
	void createBufferObjects(int index);
	void destroyBufferObjects();

	//Animation Functions
	void play();
	void refeshModelMatrix();
	void addAnimationFrame();
	void removeAnimationFrame();
	void nextAnimationFrame();
	void prevAnimationFrame();

	
	/* Draw all objects */
	void drawObjects(const glm::mat4& viewMatrix, const glm::mat4& projMatrix);

	// Intersections
	Object* checkIntersection(vec3 rayOrigin, vec3 rayDir);
	ButtonObject* checkButtonIntersection(glm::vec2);
	void updateModifiedVertexArray();

private:
	GLuint getNewVaoId();
	GLuint getNewVboId();

};



#endif
