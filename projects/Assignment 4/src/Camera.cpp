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

Camera::Camera(){
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

void Camera::rayCasting(int mouse_x, int mouse_y){
	int width = 640;
	int height = 640;

	float x = (2.0f * mouse_x) / width - 1.0f;
	float y = 1.0f - (2.0f * mouse_y) / height;
	float z = 1.0f;
	vec3 ray_nds = vec3 (x, y, z);


	vec4 ray_clip = vec4 (ray_nds.x, ray_nds.y, -1.0, 1.0);
	vec4 ray_eye = inverse (_projMatrix) * ray_clip;
	ray_eye = vec4 (ray_eye.x, ray_eye.y, -1.0, 0.0);
	vec3 ray_wor = vec3 ((inverse (_viewMatrix) * ray_eye).x, (inverse (_viewMatrix) * ray_eye).y, (inverse (_viewMatrix) * ray_eye).z);
// don't forget to normalise the vector at some point
	// ray_wor = normalize (ray_wor);

	std::cout<< ray_wor.x << "," << ray_wor.x << "," << ray_wor.z << std::endl;

	 glBegin(GL_LINE_LOOP);//start drawing a line loop
      glVertex3f(0.0f,0.0f,0.0f);//left of window
      glVertex3f(ray_wor.x,ray_wor.y,ray_wor.z);//bottom of window

    glEnd();//end drawing of line loop

	/*
	vec3 v0 = vec3 (-1, -1, 0);                                                                                                                  
	vec3 v1 = vec3 ( 1, -1, 0);                                                                                                                  
	vec3 v2 = vec3 ( 0,  1, 0);                                                                                                                                                                                                                                                                                                                                                             
	vec3 v0v1 = v1 - v0;
	vec3 v0v2 = v2 - v0;
	vec3 N = cross(v0v1, v0v2);
	float nDotRay = dot(N, r.dir);
	if (dot(N, r.dir) == 0) return false; // ray parallel to triangle 
	float d = dot(N, v0);
	float t = -(dot(N, r.orig) + d) / nDotRay;
  
	// inside-out test
	Vec3f Phit = r(t);
  
	// inside-out test edge0
	Vec3f v0p = Phit - v0;
	float v = dot(N, cross(v0v1, v0p));
	if (v < 0) return false; // P outside triangle
 
	// inside-out test edge1
	Vec3f v1p = Phit - v1;
	Vec3f v1v2 = v2 - v1;
	float w = dot(N, cross(v1v2, v1p));
	if (w < 0) return false; // P outside triangle
 
	// inside-out test edge2
	Vec3f v2p = Phit - v2;
	Vec3f v2v0 = v0 - v2;
	float u = dot(N, cross(v2v0, v2p));
	if (u < 0) return false; // P outside triangle
 
	isectData.t = t;
  
	return true;*/

	

/*
	Ray Mouse::GetPickRay(mat4 projMat, mat4 modelMat, 
                      vec4 cameraPos, 
                      int windowWidth, int windowHeight) 
{
    float mouseX = float(this->currentPosition.x);
    float mouseY = float(this->currentPosition.y);

    vec4 mousePos_clipSpace = vec4(
                                  ((mouseX * 2.0f) / windowWidth) - 1.0f,
                                  (1.0f - (2.0f * mouseY) / windowHeight), 
                                  0.0f,
                                  1.0f);

    vec4 mousePos_viewSpace = inverse(projMat) * mousePos_clipSpace;

    mousePos_viewSpace = mousePos_viewSpace / mousePos_viewSpace.w;

    vec4 mousePos_worldSpace = inverse(modelMat) * mousePos_viewSpace;

    vec4 rayDirection = normalize(mousePos_worldSpace - cameraPos);
    vec4 rayOrigin = cameraPos;

    return Ray(rayOrigin, rayDirection);
} */

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