#include "Camera.h"

#include <iostream>
#include <sstream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

const float Camera::DEFAULT_ROTATION_SPEED = 0.3f;
const float Camera::DEFAULT_FOVX = 90.0f;
const float Camera::DEFAULT_ZNEAR = 0.1f;
const float Camera::DEFAULT_ZFAR = 100.0f;
const float Camera::DEFAULT_LEFT = -2.0f;
const float Camera::DEFAULT_RIGHT = 2.0f;
const float Camera::DEFAULT_BOTTOM = -2.0f;
const float Camera::DEFAULT_TOP = 2.0f;
const float Camera::DEFAULT_DIST = -7.0f;
const float Camera::DEFAULT_RX = 10.0f;
const float Camera::DEFAULT_RY = 0.0f;

const vec3 Camera::WORLD_CENTER = vec3(0.0f, 0.0f, 0.0f);
const vec3 Camera::WORLD_XAXIS = vec3(1.0f, 0.0f, 0.0f);
const vec3 Camera::WORLD_YAXIS = vec3(0.0f, 1.0f, 0.0f);
const vec3 Camera::WORLD_ZAXIS = vec3(0.0f, 0.0f, 1.0f);

Camera::Camera(){
	_snapshotNumber = 0;
    _fovx = DEFAULT_FOVX;
	_nearVal = DEFAULT_ZNEAR;
	_farVal = DEFAULT_ZFAR;
    
	_left = DEFAULT_LEFT;
	_right = DEFAULT_RIGHT;
	_bottom = DEFAULT_BOTTOM;
	_top = DEFAULT_TOP;
	_aspect = 1;

	_dist = DEFAULT_DIST;
    _eye = vec3(0.0f, 0.0f, 0.0f);
	_target = vec3(0.0f, 0.0f, 0.0f);
	_viewMatrix = mat4();
	_projMatrix = mat4();

	_rX = DEFAULT_RX;
	_rY = DEFAULT_RY;
}

void Camera::snapshot(int windowWidth, int windowHeight){
	byte* bmpBuffer = (byte*)malloc(windowWidth*windowHeight*3);
	if (!bmpBuffer)
	return;

	glReadPixels((GLint)0, (GLint)0,
	(GLint)windowWidth-1, (GLint)windowHeight-1,
	GL_BGR, GL_UNSIGNED_BYTE, bmpBuffer);

	//Sets file number as the last unexisting one

	for(int i = 0; ; i++){
		std::stringstream ss;
		ss << "Snapshot" << i << ".bmp";
		std::string filename = ss.str();

		FILE *filePtr;
		fopen_s(&filePtr, filename.c_str(), "r");
		if(!filePtr){
			_snapshotNumber = i;
			break;
		}
		fclose(filePtr);
	}

	std::stringstream ss;
	ss << "Snapshot" << _snapshotNumber << ".bmp";
	std::string filename = ss.str();

	FILE *filePtr;
	fopen_s(&filePtr, filename.c_str(), "wb");

	if (!filePtr)
	return;

	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;

	bitmapFileHeader.bfType = 0x4D42; //"BM"
	bitmapFileHeader.bfSize = windowWidth*windowHeight*3;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits =
	sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth = windowWidth-1;
	bitmapInfoHeader.biHeight = windowHeight-1;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = 24;
	bitmapInfoHeader.biCompression = BI_RGB;
	bitmapInfoHeader.biSizeImage = 0;
	bitmapInfoHeader.biXPelsPerMeter = 0; // ?
	bitmapInfoHeader.biYPelsPerMeter = 0; // ?
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;

	fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	fwrite(bmpBuffer, windowWidth*windowHeight*3, 1, filePtr);
	fclose(filePtr);

	free(bmpBuffer);
}


vec3 Camera::getEye(){
	return _eye;
}

vec3 Camera::rayCasting(int mouse_x, int mouse_y, int width, int height){

	float x = (2.0f * mouse_x) / width - 1.0f;
	float y = 1.0f - (2.0f * mouse_y) / height;
	float z = 1.0f;
	vec3 ray_nds = vec3 (x, y, z);

	vec4 ray_clip = vec4 (ray_nds.x, ray_nds.y, -1.0, 1.0);
	vec4 ray_eye = inverse (_projMatrix) * ray_clip;
	ray_eye = vec4 (ray_eye.x, ray_eye.y, -1.0, 0.0);
	vec3 ray_wor = vec3 ((inverse (_viewMatrix) * ray_eye).x, (inverse (_viewMatrix) * ray_eye).y, (inverse (_viewMatrix) * ray_eye).z);

	ray_wor = normalize (ray_wor);

	//_line -> newLine(vec4 (_eye, 1.0f), vec4 (ray_wor.x, ray_wor.y, ray_wor.z, 0));
	//std::cout<< ray_wor.x << "," << ray_wor.x << "," << ray_wor.z << std::endl;

	return ray_wor;

}

void Camera::ExtractCameraPos()
{
  mat4 modelViewT = transpose(_viewMatrix);
 
  // Get plane normals 
  vec3 n1(modelViewT[0]);
  vec3 n2(modelViewT[1]);
  vec3 n3(modelViewT[2]);
 
  // Get plane distances
  float d1(modelViewT[0].w);
  float d2(modelViewT[1].w);
  float d3(modelViewT[2].w);
 
  // Get the intersection of these 3 planes
  // http://paulbourke.net/geometry/3planes/
  vec3 n2n3 = cross(n2, n3);
  vec3 n3n1 = cross(n3, n1);
  vec3 n1n2 = cross(n1, n2);
 
  vec3 top = (n2n3 * d1) + (n3n1 * d2) + (n1n2 * d3);
  float denom = dot(n1, n2n3);
 
  //return top / -denom;
  _eye = top/-denom;
}

void Camera::lookAt(const vec3 &eye, const vec3 &target, const vec3 &up){
	mat4 transformation1 = translate(0.0f,0.0f,_dist);
	mat4 transformation2 = rotate(_rX, vec3(1,0,0));
	mat4 transformation3 = rotate(_rY, vec3(0,1,0));
	_viewMatrix = transformation1 * transformation2 * transformation3 * mat4();
	_eye = vec3(transformation3 * transformation2 * transformation1 * vec4(0,0,0,1));
	_eye.z = -_eye.z;
}
void Camera::orthographic(const float &left, const float &right, const float &bottom, const float &top, const float &nearVal, const float &farVal){
	setBehavior(CameraProjection::CAMERA_ORTHOGRAPHIC);
	_projMatrix = glm::ortho(left, right, bottom, top, nearVal, farVal);
	_left = left; _right = right; _bottom = bottom; _top = top; _nearVal = nearVal; _farVal = farVal;
}

void Camera::perspective(const float &fovx, const float &aspect, const float &zNear, const float &zFar){
	setBehavior(CameraProjection::CAMERA_PRESPECTIVE);
	_projMatrix = glm::perspective(fovx, aspect, zNear, zFar);
    _fovx = fovx; _aspect = aspect; _nearVal = zNear; _farVal = zFar;
}

void Camera::setBehavior(CameraProjection newProjection){
	_behavior = newProjection;
}

void Camera::toggleProjection(){
	if(_behavior == CameraProjection::CAMERA_ORTHOGRAPHIC)
		perspective(_fovx, _aspect, _nearVal, _farVal);
	else
		orthographic(_left, _right, _bottom, _top, _nearVal, _farVal);
}

void Camera::updateViewMatrix(){
	lookAt(_eye, _target, _up);
}

void Camera::resetToDefault(){
	_dist = DEFAULT_DIST;
	_rX = DEFAULT_RX;
	_rY = DEFAULT_RY;
}