#include "Vector3.h"

Vector3 operator*(float lhs, const Vector3 &rhs){
    return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

Vector3 operator-(const Vector3 &v){
    return Vector3(-v.x, -v.y, -v.z);
}

Vector3 Vector3::cross(const Vector3 &p, const Vector3 &q){
    return Vector3((p.y * q.z) - (p.z * q.y),
				   (p.z * q.x) - (p.x * q.z),
				   (p.x * q.y) - (p.y * q.x));
}

float Vector3::dot(const Vector3 &p, const Vector3 &q){
    return (p.x * q.x) + (p.y * q.y) + (p.z * q.z);
}

Vector3::Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

Vector3 &Vector3::operator+=(const Vector3 &rhs){
    x += rhs.x, y += rhs.y, z += rhs.z;
    return *this;
}

bool Vector3::operator==(const Vector3 &rhs) const{
    return Math::closeEnough(x, rhs.x) && Math::closeEnough(y, rhs.y)
        && Math::closeEnough(z, rhs.z);
}

bool Vector3::operator!=(const Vector3 &rhs) const{
    return !(*this == rhs);
}

Vector3 &Vector3::operator-=(const Vector3 &rhs){
    x -= rhs.x, y -= rhs.y, z -= rhs.z;
    return *this;
}

Vector3 &Vector3::operator*=(float scalar){
    x *= scalar, y *= scalar, z *= scalar;
    return *this;
}

Vector3 &Vector3::operator/=(float scalar){
    x /= scalar, y /= scalar, z /= scalar;
    return *this;
}

Vector3 Vector3::operator+(const Vector3 &rhs) const{
    Vector3 tmp(*this);
    tmp += rhs;
    return tmp;
}

Vector3 Vector3::operator-(const Vector3 &rhs) const{
    Vector3 tmp(*this);
    tmp -= rhs;
    return tmp;
}

Vector3 Vector3::operator*(float scalar) const{
    return Vector3(x * scalar, y * scalar, z * scalar);    
}

Vector3 Vector3::operator/(float scalar) const{
    return Vector3(x / scalar, y / scalar, z / scalar);
}

float Vector3::magnitude() const{
    return sqrtf((x * x) + (y * y) + (z * z));
}

float Vector3::magnitudeSq() const{
    return (x * x) + (y * y) + (z * z);
}

Vector3 Vector3::inverse() const{
    return Vector3(-x, -y, -z);
}

void Vector3::normalize(){
    float invMag = 1.0f / magnitude();
    x *= invMag, y *= invMag, z *= invMag;
}

void Vector3::set(float x_, float y_, float z_){
    x = x_, y = y_, z = z_;
}