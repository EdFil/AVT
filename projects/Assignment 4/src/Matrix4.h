#ifndef MATRIX_H
#define MATRIX_H

#include "Math.h"
#include "Vector3.h"

class Matrix4{
    friend Vector3 operator*(const Vector3 &lhs, const Matrix4 &rhs);
    friend Matrix4 operator*(float scalar, const Matrix4 &rhs);

public:
    static const Matrix4 IDENTITY;

    Matrix4() {}
    Matrix4(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44);
    ~Matrix4() {}

    float *operator[](int row);
    const float *operator[](int row) const;

    bool operator==(const Matrix4 &rhs) const;
    bool operator!=(const Matrix4 &rhs) const;

    Matrix4 &operator+=(const Matrix4 &rhs);
    Matrix4 &operator-=(const Matrix4 &rhs);
    Matrix4 &operator*=(const Matrix4 &rhs);
    Matrix4 &operator*=(float scalar);
    Matrix4 &operator/=(float scalar);

    Matrix4 operator+(const Matrix4 &rhs) const;
    Matrix4 operator-(const Matrix4 &rhs) const;
    Matrix4 operator*(const Matrix4 &rhs) const;
    Matrix4 operator*(float scalar) const;
    Matrix4 operator/(float scalar) const;

	Matrix4 rotateX(float degrees);
	Matrix4 rotateY(float degrees);
	Matrix4 rotateZ(float degrees);
	Matrix4 translate(float x, float y, float z);
	Matrix4 translate(const Vector3 &vector);
	Matrix4 scale(float x, float y, float z);

    void fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees);
    void identity();
    void toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const;

	void lerp(const Matrix4 &matrix);
	const float *toArray() const { return *mtx; }

	void print();

private:
    float mtx[4][4];
};
#endif
