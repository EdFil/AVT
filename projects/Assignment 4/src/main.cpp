#include <iostream>
#include <sstream>
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Torso.h"
#include "ObjectManager.h"
#include "Grid.h"
#include "Back.h"
#include "Tail.h"
#include "RightLeg.h"
#include "Neck.h"
#include "Head.h"
#include "LeftLeg.h"
#include "Line.h"

#define CAPTION "--> Assignment 3 <--"
#define FPS 60

int WinX = 640, WinY = 640; //480
int WindowHandle = 0;
unsigned int FrameCount = 0;
float RotationAngleY = 0.0f, RotationAngleX = 0.0f;

int oldX=0, oldY=0, mouseX, mouseY;

Camera camera(NULL);
ObjectManager objectManager;
ShaderManager shaderManager;

Object* selectedObject = NULL;
bool objectSelected = false;
bool xPressed = false, yPressed = false, zPressed = false;
bool rightMouseButton = false;
bool leftMouseButton = false;
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
		system("pause");
		exit(EXIT_FAILURE);
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
void keyPressed(unsigned char key, int x, int y){
	static bool state = false;
	static bool projection = false;
	xPressed = false;
	yPressed = false;
	zPressed = false;
	switch(key){
		case 'x':
		case 'X':
			xPressed = true;
			break;
		case 'y':
		case 'Y':
			yPressed = true;
			break;
		case 'z':
		case 'Z':
			zPressed = true;
			break;
		case 'T':
		case 't':
			objectManager.changeTri(camera.getViewMatrix(), camera.getProjectionMatrix());
			break;
		case '3':
			if(state){
				shaderManager.setProgram(0);
				objectManager.setSelectedUniform(shaderManager.getSelectedUniformId());
				objectManager.setSelectedProgram(shaderManager.getSelectedProgram());
			}
			else{
				shaderManager.setProgram(1);
				objectManager.setSelectedUniform(shaderManager.getSelectedUniformId());
				objectManager.setSelectedProgram(shaderManager.getSelectedProgram());
			}
			state = !state;
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
	if (state == GLUT_DOWN) {
		if(button == GLUT_LEFT_BUTTON){
			leftMouseButton = true;
			selectedObject = objectManager.checkIntersection(camera.getEye(), camera.rayCasting(x, y, WinX, WinY));
			if (selectedObject != NULL)
				objectSelected = true;
		}
		if(button == GLUT_RIGHT_BUTTON){
			rightMouseButton = true;
		}
		oldX = x; 
		oldY = y; 
		mouseX=x; mouseY =y;	
	}
	else{
		objectSelected = false;
		rightMouseButton = false;
		leftMouseButton = false;
		middleMouseButton = false;
	}

}

void mouseMotion(int x, int y) {
	if(rightMouseButton && !objectSelected){
		camera.addToRY((x - oldX)/5.0f); 
		camera.addToRX((y - oldY)/5.0f); 
		oldX = x;
		oldY = y;
		camera.updateViewMatrix();
	}
	else if(leftMouseButton && objectSelected){
		if(xPressed)
			selectedObject->translateMatrix((x - oldX)/(WinX*0.175),0.0f, 0.0f);
		else if(yPressed)
			selectedObject->translateMatrix(0.0f,-(y - oldY)/(WinY*0.175), 0.0f);
		else if(zPressed)
			selectedObject->translateMatrix(0.0f,0.0f, (y - oldY)/(WinY*0.175));

		std::cout << "Translating : " << oldX << " , " << oldY << std::endl; 
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
	shaderManager = ShaderManager();
	shaderManager.addProgram("../src/MVPVertexShader.glsl", "../src/SimpleFragmentShader.glsl");
	shaderManager.addProgram("../src/OtherVertexShader.glsl", "../src/SimpleFragmentShader.glsl");
	shaderManager.createShaderProgram();
	//Line* line = new Line(vec4(0,0,0,1), vec4(0,5,0,1));
	camera = Camera(NULL);
	camera.lookAt(glm::vec3(0,5,5), glm::vec3(0,0,0), glm::vec3(0,1,0));
	camera.perspective(30, 1.0f, 0.1f, 20.0f);
	objectManager = ObjectManager(shaderManager.getSelectedUniformId(), shaderManager.getSelectedProgram());
	//objectManager.addObject(line);
	objectManager.addObject(new Grid(4,0.2f));
	objectManager.addObject(new Torso());
	objectManager.addObject(new Back());
	objectManager.addObject(new Tail());
	objectManager.addObject(new RightLeg());
	objectManager.addObject(new Neck());
	objectManager.addObject(new Head());
	objectManager.addObject(new LeftLeg());
	objectManager.createBufferObjects();
	setupCallbacks();

}

int main(int argc, char* argv[]){
	init(argc, argv);
	glutMainLoop();	
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////