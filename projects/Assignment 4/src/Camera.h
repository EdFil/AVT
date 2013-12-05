#ifndef CAMERA_H
#define CAMERA_H

#include "glm\glm.hpp"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "glm\ext.hpp"

using namespace glm;

class Camera {

	enum CameraProjection{
        CAMERA_PRESPECTIVE,
        CAMERA_ORTHOGRAPHIC
    };

	static const float DEFAULT_ROTATION_SPEED;
    static const float DEFAULT_FOVX;   
    static const float DEFAULT_ZFAR;
    static const float DEFAULT_ZNEAR;
	static const float DEFAULT_LEFT;
	static const float DEFAULT_RIGHT;
	static const float DEFAULT_BOTTOM;
	static const float DEFAULT_TOP;
	static const vec3 WORLD_CENTER;
    static const vec3 WORLD_XAXIS;
    static const vec3 WORLD_YAXIS;
    static const vec3 WORLD_ZAXIS;

	CameraProjection _behavior;
    float _fovx;
    float _nearVal;
    float _farVal;
	float _left;
	float _right;
	float _top;
	float _bottom;
	float _aspect;
	float _rX, _rY;
	float _dist;

    vec3 _eye;
    vec3 _target;
	vec3 _up;
    mat4 _viewMatrix;
    mat4 _projMatrix;
public:
	Camera();

    void lookAt(const vec3 &eye, const vec3 &target, const vec3 &up);
	void orthographic(const float &left,const float &right,const float &bottom,const float &top,const float &nearVal,const float &farVal);
    void perspective(const float &fovx, const float &aspect, const float &znear, const float &far);

	void addToRX(float value){ _rX += value; }
	void addToRY(float value){ _rY += value; }
	void addToDist(float value) { 
		_dist += value; 
		if(_dist >= -5)
			_dist = -5;
		else if(_dist <= -100)
			_dist = -100;
	}

	//-----GETTERS

	inline Camera::CameraProjection Camera::getProjection() const	{ return _behavior; }
	inline const mat4 &Camera::getProjectionMatrix() const		{ return _projMatrix; }
	inline const mat4 &Camera::getViewMatrix() const				{ return _viewMatrix; }

	// Setter methods.

    void setBehavior(CameraProjection behavior);
	void toggleProjection();
	void updateViewMatrix();
};

#endif