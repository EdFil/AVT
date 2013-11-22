#include "Quaternion.h"
#include <iostream>

const Quaternion Quaternion::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f);

Quaternion operator*(float lhs, const Quaternion &rhs){
    return rhs * lhs;
}

Quaternion::Quaternion(float w_, float x_, float y_, float z_): w(w_), x(x_), y(y_), z(z_) {}

Quaternion::Quaternion(const Vector3 &axis, float angle){
	w  = cosf( angle/2);
	x = axis.x * sinf( angle/2 );
	y = axis.y * sinf( angle/2 );
	z = axis.z * sinf( angle/2 );
}

Quaternion::Quaternion(float headDegrees, float pitchDegrees, float rollDegrees){
	fromHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
}

bool Quaternion::operator==(const Quaternion &rhs) const {
    return Math::closeEnough(w, rhs.w) && Math::closeEnough(x, rhs.x)
        && Math::closeEnough(y, rhs.y) && Math::closeEnough(z, rhs.z);
}

bool Quaternion::operator!=(const Quaternion &rhs) const{
    return !(*this == rhs);
}

Quaternion &Quaternion::operator+=(const Quaternion &rhs){
    w += rhs.w, x += rhs.x, y += rhs.y, z += rhs.z;
    return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &rhs){
    w -= rhs.w, x -= rhs.x, y -= rhs.y, z -= rhs.z;
    return *this;
}

Quaternion &Quaternion::operator*=(const Quaternion &rhs){
    // Multiply so that rotations are applied in a left to right order.
    Quaternion tmp(
        (w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z),
        (w * rhs.x) + (x * rhs.w) - (y * rhs.z) + (z * rhs.y),
        (w * rhs.y) + (x * rhs.z) + (y * rhs.w) - (z * rhs.x),
        (w * rhs.z) - (x * rhs.y) + (y * rhs.x) + (z * rhs.w));

    /*
    // Multiply so that rotations are applied in a right to left order.
    Quaternion tmp(
    (w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z),
    (w * rhs.x) + (x * rhs.w) + (y * rhs.z) - (z * rhs.y),
    (w * rhs.y) - (x * rhs.z) + (y * rhs.w) + (z * rhs.x),
    (w * rhs.z) + (x * rhs.y) - (y * rhs.x) + (z * rhs.w));
    */

    *this = tmp;
    return *this;
}

Quaternion &Quaternion::operator*=(float scalar){
    w *= scalar, x *= scalar, y *= scalar, z *= scalar;
    return *this;
}

Quaternion &Quaternion::operator/=(float scalar){
    w /= scalar, x /= scalar, y /= scalar, z /= scalar;
    return *this;
}

Quaternion Quaternion::operator+(const Quaternion &rhs) const{
    Quaternion tmp(*this);
    tmp += rhs;
    return tmp;
}

Quaternion Quaternion::operator-(const Quaternion &rhs) const{
    Quaternion tmp(*this);
    tmp -= rhs;
    return tmp;
}

Quaternion Quaternion::operator*(const Quaternion &rhs) const{
    Quaternion tmp(*this);
    tmp *= rhs;
    return tmp;
}

Quaternion Quaternion::operator*(float scalar) const{
    Quaternion tmp(*this);
    tmp *= scalar;
    return tmp;
}

Quaternion Quaternion::operator/(float scalar) const{
    Quaternion tmp(*this);
    tmp /= scalar;
    return tmp;
}

Quaternion Quaternion::conjugate() const{
    Quaternion tmp(w, -x, -y, -z);
    return tmp;
}

void Quaternion::fromAxisAngle(const Vector3 &axis, float degrees){
    float halfTheta = Math::degreesToRadians(degrees) * 0.5f;
    float s = sinf(halfTheta);
    w = cosf(halfTheta), x = axis.x * s, y = axis.y * s, z = axis.z * s;
}

inline void Quaternion::fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees){
    Matrix4 m;
    m.fromHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
    fromMatrix(m);
}

void Quaternion::identity(){
    w = 1.0f, x = y = z = 0.0f;
}

Quaternion Quaternion::inverse() const{
    float invMag = 1.0f / magnitude();
    return conjugate() * invMag;
}

float Quaternion::magnitude() const{
    return sqrtf(w * w + x * x + y * y + z * z);
}

void Quaternion::normalize(){
    float invMag = 1.0f / magnitude();
    w *= invMag, x *= invMag, y *= invMag, z *= invMag;
}

inline void Quaternion::set(float w_, float x_, float y_, float z_)
{
    w = w_, x = x_, y = y_, z = z_;
}

void Quaternion::toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const{
    Matrix4 m = toMatrix4();
    m.toHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
}

void Quaternion::fromMatrix(const Matrix4 &m){
    // Creates a quaternion from a rotation matrix. 
    // The algorithm used is from Allan and Mark Watt's "Advanced 
    // Animation and Rendering Techniques" (ACM Press 1992).

    float s = 0.0f;
    float q[4] = {0.0f};
    float trace = m[0][0] + m[1][1] + m[2][2];

    if (trace > 0.0f)
    {
        s = sqrtf(trace + 1.0f);
        q[3] = s * 0.5f;
        s = 0.5f / s;
        q[0] = (m[1][2] - m[2][1]) * s;
        q[1] = (m[2][0] - m[0][2]) * s;
        q[2] = (m[0][1] - m[1][0]) * s;
    }
    else
    {
        int nxt[3] = {1, 2, 0};
        int i = 0, j = 0, k = 0;

        if (m[1][1] > m[0][0])
            i = 1;

        if (m[2][2] > m[i][i])
            i = 2;

        j = nxt[i];
        k = nxt[j];
        s = sqrtf((m[i][i] - (m[j][j] + m[k][k])) + 1.0f);

        q[i] = s * 0.5f;
        s = 0.5f / s;
        q[3] = (m[j][k] - m[k][j]) * s;
        q[j] = (m[i][j] + m[j][i]) * s;
        q[k] = (m[i][k] + m[k][i]) * s;
    }

    x = q[0], y = q[1], z = q[2], w = q[3];
}

void Quaternion::toAxisAngle(Vector3 &axis, float &degrees) const{
    // Converts this quaternion to an axis and an angle.

    float sinHalfThetaSq = 1.0f - w * w;

    // Guard against numerical imprecision and identity quaternions.
    if (sinHalfThetaSq <= 0.0f)
    {
        axis.x = 1.0f, axis.y = axis.z = 0.0f;
        degrees = 0.0f;
    }
    else
    {
        float invSinHalfTheta = 1.0f / sqrtf(sinHalfThetaSq);

        axis.x = x * invSinHalfTheta;
        axis.y = y * invSinHalfTheta;
        axis.z = z * invSinHalfTheta;
        degrees = Math::radiansToDegrees(2.0f * acosf(w));
    }
}

Matrix4 Quaternion::toMatrix4() const{
    // Converts this quaternion to a rotation matrix.
    //
    //  | 1 - 2(y^2 + z^2)	2(xy + wz)			2(xz - wy)			0  |
    //  | 2(xy - wz)		1 - 2(x^2 + z^2)	2(yz + wx)			0  |
    //  | 2(xz + wy)		2(yz - wx)			1 - 2(x^2 + y^2)	0  |
    //  | 0					0					0					1  |

    float x2 = x + x; 
    float y2 = y + y; 
    float z2 = z + z;
    float xx = x * x2;
    float xy = x * y2;
    float xz = x * z2;
    float yy = y * y2;
    float yz = y * z2;
    float zz = z * z2;
    float wx = w * x2;
    float wy = w * y2;
    float wz = w * z2;

    Matrix4 m;

    m[0][0] = 1.0f - (yy + zz);
    m[0][1] = xy + wz;
    m[0][2] = xz - wy;
    m[0][3] = 0.0f;

    m[1][0] = xy - wz;
    m[1][1] = 1.0f - (xx + zz);
    m[1][2] = yz + wx;
    m[1][3] = 0.0f;

    m[2][0] = xz + wy;
    m[2][1] = yz - wx;
    m[2][2] = 1.0f - (xx + yy);
    m[2][3] = 0.0f;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;

    return m;
}

void Quaternion::print(){
	std::cout.precision(5);
	std::cout << std::fixed << "[" << x << ", " << y << ", " << z << "] - " << w << std::endl;
}