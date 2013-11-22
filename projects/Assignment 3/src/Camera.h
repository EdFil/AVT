#ifndef CAMERA_H
#define CAMERA_H

#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "GL\glew.h"
#include "GL\freeglut.h"

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
	static const Vector3 WORLD_CENTER;
    static const Vector3 WORLD_XAXIS;
    static const Vector3 WORLD_YAXIS;
    static const Vector3 WORLD_ZAXIS;

	CameraProjection _behavior;
    float _longitudeDegrees;
    float _latitudeDegrees;
    float _fovx;
    float _nearVal;
    float _farVal;
	float _left;
	float _right;
	float _top;
	float _bottom;
	float _aspectRatio;

    Vector3 _eye;
    Vector3 _target;
    Vector3 _offset;
    Vector3 _xAxis;
    Vector3 _yAxis;
    Vector3 _zAxis;
    Vector3 _viewDir;
    Matrix4 _viewMatrix;
    Matrix4 _projMatrix;
    Quaternion _orientation;

public:
	Camera();

    void lookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up);
	void orthographic(float left, float right, float bottom, float top, float nearVal, float farVal);
    void perspective(float fovx, float aspect, float znear, float zfar);
    void rotate(float latitudeDegrees, float longitudeDegrees);

	//-----GETTERS

	inline Camera::CameraProjection Camera::getProjection() const	{ return _behavior; }
	inline const Matrix4 &Camera::getProjectionMatrix() const		{ return _projMatrix; }
	inline const Vector3 &Camera::getViewDirection() const			{ return _viewDir; }
	inline const Matrix4 &Camera::getViewMatrix() const				{ return _viewMatrix; }

	// Setter methods.

    void setBehavior(CameraProjection behavior);
	void toggleProjection();

private:
	void updateViewMatrix();
};

#endif