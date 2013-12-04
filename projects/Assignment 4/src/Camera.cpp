#include "Camera.h"

#include <iostream>
#include "glm\glm.hpp"
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

const vec3 Camera::WORLD_CENTER = vec3(0.0f, 0.0f, 0.0f);
const vec3 Camera::WORLD_XAXIS = vec3(1.0f, 0.0f, 0.0f);
const vec3 Camera::WORLD_YAXIS = vec3(0.0f, 1.0f, 0.0f);
const vec3 Camera::WORLD_ZAXIS = vec3(0.0f, 0.0f, 1.0f);

Camera::Camera(Line* line) : _line(line){
    _fovx = DEFAULT_FOVX;
	_nearVal = DEFAULT_ZNEAR;
	_farVal = DEFAULT_ZFAR;
    
	_left = DEFAULT_LEFT;
	_right = DEFAULT_RIGHT;
	_bottom = DEFAULT_BOTTOM;
	_top = DEFAULT_TOP;
	_aspect = 1;

    _eye = vec3(0.0f, 0.0f, 0.0f);
	_target = vec3(0.0f, 0.0f, 0.0f);
	_viewMatrix = mat4();
	_projMatrix = mat4();

	_rX = 15;
	_rY = 0;
}

void Camera::lookAt(const vec3 &eye, const vec3 &target, const vec3 &up){
	mat4 transformation1 = translate(0.0f,0.0f,-10.0f);
	mat4 transformation2 = rotate(_rX, vec3(1,0,0));
	mat4 transformation3 = rotate(_rY, vec3(0,1,0));
	_viewMatrix = transformation1 * transformation2 * transformation3 * mat4();
	//_viewMatrix = glm::lookAt(eye, target, up);
	//_viewMatrix *= toMat4(_orientation);

	_eye = eye; _target = target; _up = up;
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