#include "Camera.h"

#include <iostream>

const float Camera::DEFAULT_ROTATION_SPEED = 0.3f;
const float Camera::DEFAULT_FOVX = 90.0f;
const float Camera::DEFAULT_ZNEAR = 0.1f;
const float Camera::DEFAULT_ZFAR = 100.0f;
const float Camera::DEFAULT_LEFT = -2.0f;
const float Camera::DEFAULT_RIGHT = 2.0f;
const float Camera::DEFAULT_BOTTOM = -2.0f;
const float Camera::DEFAULT_TOP = 2.0f;

const Vector3 Camera::WORLD_CENTER = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Camera::WORLD_XAXIS = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Camera::WORLD_YAXIS = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Camera::WORLD_ZAXIS = Vector3(0.0f, 0.0f, 1.0f);

Camera::Camera(){
    _fovx = DEFAULT_FOVX;
    _aspectRatio = 1.0f;
	_nearVal = DEFAULT_ZNEAR;
	_farVal = DEFAULT_ZFAR;
    
	_left = DEFAULT_LEFT;
	_right = DEFAULT_RIGHT;
	_bottom = DEFAULT_BOTTOM;
	_top = DEFAULT_TOP;

    _eye = Vector3(0.0f, 0.0f, 0.0f);
	_target = Vector3(0.0f, 0.0f, 0.0f);
	_offset = Vector3(0.0f, 0.0f, 0.0f);

    _xAxis = Vector3(1.0f, 0.0f, 0.0f);
    _yAxis = Vector3(0.0f, 1.0f, 0.0f);
    _zAxis = Vector3(0.0f, 0.0f, 1.0f);
    _viewDir = Vector3(0.0f, 0.0f, 1.0f);
    
	_orientation = Quaternion::IDENTITY;

	_viewMatrix = Matrix4();
	_projMatrix = Matrix4();
}

void Camera::lookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up){
    _eye = eye;
	//if(_eye.x == 0.0f) _eye.x = 0.000001f;
	//if(_eye.y == 0.0f) _eye.y = 0.000001f;
	//if(_eye.z == 0.0f) _eye.z = 0.000001f;

    _offset = _zAxis = _eye - target;
    _zAxis.normalize();

    _viewDir = -_zAxis;

    _xAxis = Vector3::cross(up, _zAxis);
    _xAxis.normalize();

    _yAxis = Vector3::cross(_zAxis, _xAxis);
    _yAxis.normalize();
    _xAxis.normalize();

    _viewMatrix[0][0] = _xAxis.x;
    _viewMatrix[1][0] = _xAxis.y;
    _viewMatrix[2][0] = _xAxis.z;
    _viewMatrix[3][0] = -Vector3::dot(_xAxis, _eye);

    _viewMatrix[0][1] = _yAxis.x;
    _viewMatrix[1][1] = _yAxis.y;
    _viewMatrix[2][1] = _yAxis.z;
    _viewMatrix[3][1] = -Vector3::dot(_yAxis, _eye);

    _viewMatrix[0][2] = _zAxis.x;
    _viewMatrix[1][2] = _zAxis.y;
    _viewMatrix[2][2] = _zAxis.z;    
    _viewMatrix[3][2] = -Vector3::dot(_zAxis, _eye);

	_viewMatrix[0][3] = 0.0f;
	_viewMatrix[1][3] = 0.0f;
	_viewMatrix[2][3] = 0.0f;
	_viewMatrix[3][3] = 1.0f;

    _orientation.fromMatrix(_viewMatrix);
}

void Camera::orthographic(float left, float right, float bottom, float top, float nearVal, float farVal){
	setBehavior(CameraProjection::CAMERA_ORTHOGRAPHIC);
    _projMatrix[0][0] = 2 / (right-left);
    _projMatrix[0][1] = 0.0f;
    _projMatrix[0][2] = 0.0f;
    _projMatrix[0][3] = -(right + left) / (right - left);

    _projMatrix[1][0] = 0.0f;
    _projMatrix[1][1] = 2 / (top-bottom);
    _projMatrix[1][2] = 0.0f;
    _projMatrix[1][3] = -(top  +bottom) / (top - bottom);

    _projMatrix[2][0] = 0.0f;
    _projMatrix[2][1] = 0.0f;
    _projMatrix[2][2] = -2 / (farVal-nearVal);
    _projMatrix[2][3] = 0.0f;

    _projMatrix[3][0] = 0.0f;
    _projMatrix[3][1] = 0.0f;
    _projMatrix[3][2] = -(farVal + nearVal)/(farVal - nearVal);
    _projMatrix[3][3] = 1.0f;

	_left = left; _right = right; _bottom = bottom; _top = top; _nearVal = nearVal; _farVal = farVal;
}

void Camera::perspective(float fovx, float aspect, float znear, float zfar){
    // Construct a projection matrix based on the horizontal field of view
    // 'fovx' rather than the more traditional vertical field of view 'fovy'.
	setBehavior(CameraProjection::CAMERA_PRESPECTIVE);

    float e = 1.0f / tanf(Math::degreesToRadians(fovx) / 2.0f);
    float aspectInv = 1.0f / aspect;
    float fovy = 2.0f * atanf(aspectInv / e);
    float xScale = 1.0f / tanf(0.5f * fovy);
    float yScale = xScale / aspectInv;

    _projMatrix[0][0] = xScale;
    _projMatrix[0][1] = 0.0f;
    _projMatrix[0][2] = 0.0f;
    _projMatrix[0][3] = 0.0f;

    _projMatrix[1][0] = 0.0f;
    _projMatrix[1][1] = yScale;
    _projMatrix[1][2] = 0.0f;
    _projMatrix[1][3] = 0.0f;

    _projMatrix[2][0] = 0.0f;
    _projMatrix[2][1] = 0.0f;
    _projMatrix[2][2] = (zfar + znear) / (znear - zfar);
    _projMatrix[2][3] = -1.0f;

    _projMatrix[3][0] = 0.0f;
    _projMatrix[3][1] = 0.0f;
    _projMatrix[3][2] = (2.0f * zfar * znear) / (znear - zfar);
    _projMatrix[3][3] = 0.0f;

    _fovx = fovx;
    _aspectRatio = aspect;
	_nearVal = znear;
	_farVal = zfar;
}

void Camera::setBehavior(CameraProjection newProjection){
	_behavior = newProjection;
}

void Camera::rotate(float latitudeDegrees, float longitudeDegrees){
	_latitudeDegrees = latitudeDegrees;
	_longitudeDegrees = longitudeDegrees;

	updateViewMatrix();
}

void Camera::toggleProjection(){
	if(_behavior == CameraProjection::CAMERA_ORTHOGRAPHIC){
		perspective(_fovx, _aspectRatio, _nearVal, _farVal);
	} else {
		orthographic(_left, _right, _bottom, _top, _nearVal, _farVal);
	}
}

void Camera::updateViewMatrix(){
	Quaternion rotation(_longitudeDegrees, _latitudeDegrees, 0.0f);
    Quaternion offsetVector(0.0f, _offset.x, _offset.y, _offset.z);
    Quaternion result = rotation.conjugate() * offsetVector * rotation;

    Vector3 transformedOffsetVector(result.x, result.y, result.z);
    Vector3 newCameraPosition = transformedOffsetVector + _target;

    lookAt(newCameraPosition, _target, WORLD_YAXIS);
}