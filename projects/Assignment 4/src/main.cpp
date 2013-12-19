#include <iostream>
#include <sstream>
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "Camera.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "ObjectManager.h"
#include "ObjObject.h"
#include "Grid.h"
#include "XMLObject.h"
#include "Line.h"


#define CAPTION "--> Assignment 3 <--"
#define FPS 60

int WinX = 640, WinY = 640; //480
int WindowHandle = 0;
unsigned int FrameCount = 0;
float RotationAngleY = 0.0f, RotationAngleX = 0.0f;

int oldX=0, oldY=0, mouseX, mouseY;

Camera camera;
ObjectManager objectManager;
ShaderManager shaderManager;
Line axisLine;

Object* selectedObject = NULL;
bool objectSelected = false;
bool objectWasDoubleClicked = false;
bool xPressed = false, yPressed = false, zPressed = false;
bool rightMouseButton = false;
bool leftMouseButton = false;
int lastMouseLeftClick;
bool middleMouseButton = false;

/////////////////////////////////////////////////////////////////////// ERRORS

static bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void checkOpenGLError(std::string error)
{
	if(isOpenGLError()) {
		std::cerr << error << std::endl;
		std::cerr << "EXITING" << std::endl;
		//system("pause");
		//exit(EXIT_FAILURE);
	}
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void createBufferObjects(){
	objectManager.createBufferObjects();
	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void destroyBufferObjects(){
	objectManager.destroyBufferObjects();
	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}

/////////////////////////////////////////////////////////////////////// SCENE

void callDisplay(int value){
	glutPostRedisplay();
	glutTimerFunc(1000/FPS , callDisplay , 0);
}

void drawScene(){
	objectManager.createBufferObjects(0);
	objectManager.drawObjects(camera.getViewMatrix(), camera.getProjectionMatrix());
	checkOpenGLError("ERROR: Could not draw scene.");
	
}

/////////////////////////////////////////////////////////////////////// CALLBACKS
void specialFunc(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
			objectManager.prevAnimationFrame();
			if(selectedObject != NULL)
				selectedObject->unselect();
			axisLine.setVisible(false);
			break;
		case GLUT_KEY_RIGHT:
			objectManager.nextAnimationFrame();
			if(selectedObject != NULL)
				selectedObject->unselect();
			axisLine.setVisible(false);
			break;
	}
}

void keyPressed(unsigned char key, int x, int y){
	static bool state = false;
	static bool projection = false;
	switch(key){
		case 27:
			xPressed = false; yPressed = false; zPressed = false;
			axisLine.setVisible(false);
			if(selectedObject != NULL)
				selectedObject->unselect();
			selectedObject = NULL;
			objectWasDoubleClicked = false;
			break;
		case '+':
			objectManager.addAnimationFrame();
			break;
		case '-':
			objectManager.removeAnimationFrame();
			break;
		case GLUT_KEY_LEFT:
			objectManager.prevAnimationFrame();
			break;
		case GLUT_KEY_RIGHT:
			objectManager.nextAnimationFrame();
			break;
		case 'x':
		case 'X':
			xPressed = true; yPressed = false; zPressed = false;
			if(selectedObject != NULL)
				if(xPressed)
					axisLine.setVisible(true);
				else
					axisLine.setVisible(false);
			axisLine.setToAxis(glm::vec3(1,0,0));
			break;
		case 'y':
		case 'Y':
			yPressed = true; xPressed = false; zPressed = false;
			if(selectedObject != NULL)
				if(yPressed)
					axisLine.setVisible(true);
				else
					axisLine.setVisible(false);
			axisLine.setToAxis(glm::vec3(0,1,0));
			break;
		case 'z':
		case 'Z':
			zPressed = true; xPressed = false; yPressed = false;
			if(selectedObject != NULL)
				if(zPressed)
					axisLine.setVisible(true);
				else
					axisLine.setVisible(false);
			axisLine.setToAxis(glm::vec3(0,0,1));
			break;
		case 'p':
			camera.toggleProjection();
			break;
		case 'q':
		case 'Q':
			glutExit();
			break;
	}
}

void mouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){
			leftMouseButton = true;
			Object* object = objectManager.checkIntersection(camera.getEye(), camera.rayCasting(x, y, WinX, WinY));
			if (object != NULL){ // If we hit an object
				if((glutGet(GLUT_ELAPSED_TIME) - lastMouseLeftClick) < 300)
					objectWasDoubleClicked = true;
				else
					objectWasDoubleClicked = false;
				if(selectedObject != NULL)
					selectedObject->unselect();
				selectedObject = object;
				selectedObject->select();
				axisLine.bindToObject(selectedObject);
				objectSelected = true;
			}
			else{
				objectWasDoubleClicked = false;
			}
			lastMouseLeftClick = glutGet(GLUT_ELAPSED_TIME);
		}else{
			if(!objectWasDoubleClicked){
				objectSelected = false;
				if(selectedObject != NULL){
					axisLine.setVisible(false);
					selectedObject->unselect();
					selectedObject = NULL;
				}
			}
			leftMouseButton = false;
					
		}
	}
	if(button == GLUT_RIGHT_BUTTON){
		if(state == GLUT_DOWN)
			rightMouseButton = true;
		else
			rightMouseButton = false;
	}
	if(button == 3){ //UP WHEEL
		if(objectSelected && (xPressed || yPressed || zPressed) && axisLine.isVisible()){
			if(xPressed)
				selectedObject->rotate(5,vec3(1,0,0));
			else if(yPressed)
				selectedObject->rotate(5,vec3(0,1,0));
			else if(zPressed)
				selectedObject->rotate(5,vec3(0,0,1));
		}else{
			camera.addToDist(0.2);
			camera.updateViewMatrix();
		}
	}
	if(button == 4){ //DOWN WHEEL
		if(objectSelected && (xPressed || yPressed || zPressed) && axisLine.isVisible()){
			if(xPressed)
				selectedObject->rotate(-5,vec3(1,0,0));
			else if(yPressed)
				selectedObject->rotate(-5,vec3(0,1,0));
			else if(zPressed)
				selectedObject->rotate(-5,vec3(0,0,1));
		}else{
			camera.addToDist(-0.2);
			camera.updateViewMatrix();
		}
	}
	//Refresh mouse positions
	oldX = mouseX = x; 
	oldY = mouseY = y;

}

void mouseMotion(int x, int y) {
	if(rightMouseButton && !leftMouseButton){
		camera.addToRY((x - oldX)/5.0f); 
		camera.addToRX((y - oldY)/5.0f); 
		camera.updateViewMatrix();
		objectManager.updateModifiedVertexArray();
	}
	else if(leftMouseButton && objectSelected && axisLine.isVisible()){
		if(xPressed)
			selectedObject->translate((x - oldX)/(WinX*0.175),0.0f, 0.0f);
		else if(yPressed)
			selectedObject->translate(0.0f,-(y - oldY)/(WinY*0.175), 0.0f);
		else if(zPressed)
			selectedObject->translate(0.0f,0.0f, (y - oldY)/(WinY*0.175));
	}
	oldX = x;
	oldY = y;
}

void cleanup(){
	shaderManager.destroyShaderProgram();
	checkOpenGLError("ERROR: Could not destroy shaders.");
	objectManager.destroyBufferObjects();
	checkOpenGLError("ERROR: Could not destroy buffers.");
	
}

void display(){
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawScene();
	glutSwapBuffers();
}

void idle(){ }

void reshape(int w, int h){
	WinX = w;
	WinY = h;
	glViewport(0, 0, WinX, WinY);
}

void timer(int value){
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
    FrameCount = 0;
    glutTimerFunc(1000, timer, 0);
}

/////////////////////////////////////////////////////////////////////// SETUP

void setupCallbacks() {
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialFunc);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutTimerFunc(0,callDisplay,0);
}

void setupOpenGL() {
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit() ; 
	if (result != GLEW_OK) { 
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	} 
	GLenum err_code = glGetError();
}

void setupGLUT(int argc, char* argv[]){
	glutInit(&argc, argv);
	
	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	
	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	WindowHandle = glutCreateWindow(CAPTION);
	if(WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void init(int argc, char* argv[]){
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	TextureManager::Inst();
	shaderManager = ShaderManager();
	shaderManager.addTextureProgram("NormalShader", "../src/shaders/VertexShader.glsl", "../src/shaders/FragmentShader.glsl");
	shaderManager.addTextureProgram("SelectedShader", "../src/shaders/SelectedVertexShader.glsl", "../src/shaders/FragmentShader.glsl");
	shaderManager.addSimpleProgram("SimpleShader", "../src/shaders/SimpleVertexShader.glsl", "../src/shaders/SimpleFragmentShader.glsl");
	shaderManager.createShaderProgram();
	axisLine = Line();
	camera = Camera();
	camera.lookAt(glm::vec3(0,5,5), glm::vec3(0,0,0), glm::vec3(0,1,0));
	camera.perspective(45, 1.0f, 0.1f, 10020.0f);
	objectManager = ObjectManager(&shaderManager);
	TextureManager::Inst();
	objectManager.addObject(&axisLine);
	//objectManager.addObject(new Grid(4,0.2f));
	Object* plane = new ObjObject("../src/objs/plane.obj");
	plane->setAsNonSelectable();
	objectManager.addObject(plane);
	objectManager.addObject(new XMLObject("Neck", glm::vec3(0,.2,0)));
	//objectManager.addObject(new XMLObject("Neck", glm::vec3(-0.8,.2,0)));
	//objectManager.addObject(new Torso());
	//objectManager.addObject(new Back());
	//objectManager.addObject(new Tail());
	//objectManager.addObject(new RightLeg());
	//objectManager.addObject(new Neck());
	//objectManager.addObject(new Head());
	//objectManager.addObject(new LeftLeg());
	objectManager.createBufferObjects();
	setupCallbacks();
	objectManager.updateModifiedVertexArray();

}

int main(int argc, char* argv[]){
	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////