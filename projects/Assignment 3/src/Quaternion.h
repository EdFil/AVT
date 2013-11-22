#ifndef QUATERNION_H
#define QUATERNION_H

#include "Math.h"
#include "Matrix4.h"
#include "Vector3.h"

class Quaternion{
    
	friend Quaternion operator*(float lhs, const Quaternion &rhs);

public:
    static const Quaternion IDENTITY;

    float w, x, y, z;

    Quaternion() {}
	Quaternion(const Vector3 &axis, float angle);
    Quaternion(float w_, float x_, float y_, float z_);
	Quaternion(float headDegrees, float pitchDegrees, float rollDegrees);
    ~Quaternion() {}

    bool operator==(const Quaternion &rhs) const;
    bool operator!=(const Quaternion &rhs) const;

    Quaternion &operator+=(const Quaternion &rhs);
    Quaternion &operator-=(const Quaternion &rhs);
    Quaternion &operator*=(const Quaternion &rhs);
    Quaternion &operator*=(float scalar);
    Quaternion &operator/=(float scalar);

    Quaternion operator+(const Quaternion &rhs) const;
    Quaternion operator-(const Quaternion &rhs) const;
    Quaternion operator*(const Quaternion &rhs) const;
    Quaternion operator*(float scalar) const;
    Quaternion operator/(float scalar) const;

    Quaternion conjugate() const;
    void fromAxisAngle(const Vector3 &axis, float degrees);
    void fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees);
    void fromMatrix(const Matrix4 &m);
    void identity();
    Quaternion inverse() const;
    float magnitude() const;
    void normalize();
    void set(float w_, float x_, float y_, float z_);
    void toAxisAngle(Vector3 &axis, float &degrees) const;
    void toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const;
    Matrix4 toMatrix4() const;

	void print();
};
#endif