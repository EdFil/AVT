#ifndef VECTOR3_H
#define VECTOR3_H

#include "Math.h"

class Vector3{
    friend Vector3 operator*(float lhs, const Vector3 &rhs);
    friend Vector3 operator-(const Vector3 &v);

public:
    float x, y, z;

    static Vector3 cross(const Vector3 &p, const Vector3 &q);
    static float dot(const Vector3 &p, const Vector3 &q);

    Vector3() {}
    Vector3(float x_, float y_, float z_);
    ~Vector3() {}

    bool operator==(const Vector3 &rhs) const;
    bool operator!=(const Vector3 &rhs) const;

    Vector3 &operator+=(const Vector3 &rhs);
    Vector3 &operator-=(const Vector3 &rhs);
    Vector3 &operator*=(float scalar);
    Vector3 &operator/=(float scalar);

    Vector3 operator+(const Vector3 &rhs) const;
    Vector3 operator-(const Vector3 &rhs) const;
    Vector3 operator*(float scalar) const;
    Vector3 operator/(float scalar) const;

    float magnitude() const;
    float magnitudeSq() const;
    Vector3 inverse() const;
    void normalize();
    void set(float x_, float y_, float z_);

	void print();
};

#endif
