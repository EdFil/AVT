#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Camera.h"
#include "ObjectManager.h"
#include "ShaderManager.h"

class SceneManager {
	
	Camera _camera;
	ObjectManager _objectManager;
	ShaderManager _shaderManager;

public:

	SceneManager();

	void destroyShaderProgram();

	void createBufferObjects();
	void destroyBufferObjects();

	void drawObjects();

	//Matrix4* getViewMatrix() const { return _camera->getViewMatrix(); }
	//Matrix4* getProjectionMatrix() const { return _camera->getProjectionMatrix(); }

	//void printView() { _camera->getViewMatrix()->print(); }
	//void printProj() { _camera->getProjectionMatrix()->print(); }
};



#endif
