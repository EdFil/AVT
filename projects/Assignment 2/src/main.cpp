///////////////////////////////////////////////////////////////////////
//
// Assignment 2 consists in the following:
//
// - Rewrite the program using C++ classes for:
//   - Matrix manipulation;
//   - Shader manipulation;
//   - Managing drawable entities.
//
// - Provide an UML diagram of your solution.
//
// - Add the following functionality:
//   - Read shader code from external files;
//   - Check shader compilation and linkage for error messages.
// 
// - Draw the following scene, minimizing the number of vertices on the GPU:
//   - A set of 7 TANs (i.e. TANGRAM shapes) of different colors;
//   - A flat surface on which the TANs will be placed (with an appropriate contrasting color).
//
// - Alternate between the following dispositions when the user presses the 't' key;
//   - The 7 TANs in their original square configuration;
//   - The 7 TANs put together to form a shape of your choice (6500 to choose from!);
//   - The silhouette of the shape of your choice on the flat surface.
//
// Further suggestions to verify your understanding of the concepts explored:
//
// - Use linear interpolation to create a transition between the two TAN configurations.
// - Parse geometrical information from external XML files.
//
// (c) 2013 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "ObjectManager.h"
#include "ShaderManager.h"
#include "Torso.h"
#include "Back.h"
#include "Tail.h"
#include "RightLeg.h"
#include "Neck.h"
#include "Head.h"
#include "LeftLeg.h"

#define CAPTION "Hello New World"
#define FPS 60

int WinX = 640, WinY = 640; //480
int WindowHandle = 0;
unsigned int FrameCount = 0;

ObjectManager *objectManager;
ShaderManager *shaderManager;

GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId;

/////////////////////////////////////////////////////////////////////// ERRORS

bool isOpenGLError() {
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

void createShaderProgram(){

	shaderManager->createShaderProgram();

	checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{

	shaderManager->destroyShaderProgram();

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void createBufferObjects(){
	objectManager->createBufferObjects();
	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void destroyBufferObjects(){
	objectManager->destroyBufferObjects();
	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}

/////////////////////////////////////////////////////////////////////// SCENE

void callDisplay(int value){
	glutPostRedisplay();
	glutTimerFunc(1000/FPS , callDisplay , 0);
}

void drawScene()
{
	glUseProgram(shaderManager->getSelectedShader());

	objectManager->drawObjects();

	glUseProgram(0);
	glBindVertexArray(0);

	checkOpenGLError("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// CALLBACKS
void keyPressed(unsigned char key, int x, int y){
	static bool state = false;
	if(key == '1')
		objectManager->changeTri(0);
	if(key == '2')
		objectManager->changeTri(1);
	if(key == '3'){
		if(state)
			shaderManager->setSelectedShader(0);
		else
			shaderManager->setSelectedShader(1);
		state = !state;
	}
}

void cleanup(){
	destroyShaderProgram();
	objectManager->destroyBufferObjects();
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
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
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
	shaderManager = new ShaderManager();
	shaderManager->addProgram("../src/SimpleVertexShader.glsl", "../src/SimpleFragmentShader.glsl");
	shaderManager->addProgram("../src/OtherVertexShader.glsl", "../src/SimpleFragmentShader.glsl");
	createShaderProgram();
	objectManager = new ObjectManager(shaderManager->getSelectedUniformId());
	objectManager->addObject(new Torso());
	objectManager->addObject(new Back());
	objectManager->addObject(new Tail());
	objectManager->addObject(new RightLeg());
	objectManager->addObject(new Neck());
	objectManager->addObject(new Head());
	objectManager->addObject(new LeftLeg());
	createBufferObjects();
	setupCallbacks();

}

int main(int argc, char* argv[]){
	init(argc, argv);
	glutMainLoop();	
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////