#include "SceneManager.h"
#include "Grid.h"

SceneManager::SceneManager(){
	_shaderManager = ShaderManager();
	_shaderManager.addProgram("../src/MVPVertexShader.glsl", "../src/SimpleFragmentShader.glsl");
	//_shaderManager.addProgram("../src/OtherVertexShader.glsl", "../src/SimpleFragmentShader.glsl");
	//_shaderManager.createShaderProgram();
	_camera = Camera();
	_objectManager = ObjectManager(_shaderManager.getSelectedUniformId(), _shaderManager.getSelectedProgram());
	_objectManager.addObject(new Grid(2,0.2f));
}


void SceneManager::destroyShaderProgram(){
	_shaderManager.destroyShaderProgram();
}

void SceneManager::createBufferObjects(){
	_objectManager.createBufferObjects();
}
void SceneManager::destroyBufferObjects(){
	_objectManager.destroyBufferObjects();
}

void SceneManager::drawObjects(){
	_objectManager.drawObjects(_camera.getViewMatrix(), _camera.getProjectionMatrix());
}