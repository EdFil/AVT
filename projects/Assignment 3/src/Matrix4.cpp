#include "Matrix4.h"

Vector3 operator*(const Vector3 &lhs, const Matrix4 &rhs){
    return Vector3((lhs.x * rhs.mtx[0][0]) + (lhs.y * rhs.mtx[1][0]) + (lhs.z * rhs.mtx[2][0]),
        (lhs.x * rhs.mtx[0][1]) + (lhs.y * rhs.mtx[1][1]) + (lhs.z * rhs.mtx[2][1]),
        (lhs.x * rhs.mtx[0][2]) + (lhs.y * rhs.mtx[1][2]) + (lhs.z * rhs.mtx[2][2]));
}

Matrix4 operator*(float scalar, const Matrix4 &rhs){
    return rhs * scalar;
}

Matrix4::Matrix4(float m11, float m12, float m13, float m14,
                 float m21, float m22, float m23, float m24,
                 float m31, float m32, float m33, float m34,
                 float m41, float m42, float m43, float m44){
    mtx[0][0] = m11, mtx[0][1] = m12, mtx[0][2] = m13, mtx[0][3] = m14;
    mtx[1][0] = m21, mtx[1][1] = m22, mtx[1][2] = m23, mtx[1][3] = m24;
    mtx[2][0] = m31, mtx[2][1] = m32, mtx[2][2] = m33, mtx[2][3] = m34;
    mtx[3][0] = m41, mtx[3][1] = m42, mtx[3][2] = m43, mtx[3][3] = m44;
}

float *Matrix4::operator[](int row){
    return mtx[row];
}

const float *Matrix4::operator[](int row) const{
    return mtx[row];
}

bool Matrix4::operator==(const Matrix4 &rhs) const{
    return Math::closeEnough(mtx[0][0], rhs.mtx[0][0])
        && Math::closeEnough(mtx[0][1], rhs.mtx[0][1])
        && Math::closeEnough(mtx[0][2], rhs.mtx[0][2])
        && Math::closeEnough(mtx[0][3], rhs.mtx[0][3])
        && Math::closeEnough(mtx[1][0], rhs.mtx[1][0])
        && Math::closeEnough(mtx[1][1], rhs.mtx[1][1])
        && Math::closeEnough(mtx[1][2], rhs.mtx[1][2])
        && Math::closeEnough(mtx[1][3], rhs.mtx[1][3])
        && Math::closeEnough(mtx[2][0], rhs.mtx[2][0])
        && Math::closeEnough(mtx[2][1], rhs.mtx[2][1])
        && Math::closeEnough(mtx[2][2], rhs.mtx[2][2])
        && Math::closeEnough(mtx[2][3], rhs.mtx[2][3])
        && Math::closeEnough(mtx[3][0], rhs.mtx[3][0])
        && Math::closeEnough(mtx[3][1], rhs.mtx[3][1])
        && Math::closeEnough(mtx[3][2], rhs.mtx[3][2])
        && Math::closeEnough(mtx[3][3], rhs.mtx[3][3]);
}

bool Matrix4::operator!=(const Matrix4 &rhs) const{
    return !(*this == rhs);
}

Matrix4 &Matrix4::operator+=(const Matrix4 &rhs){
    mtx[0][0] += rhs.mtx[0][0], mtx[0][1] += rhs.mtx[0][1], mtx[0][2] += rhs.mtx[0][2], mtx[0][3] += rhs.mtx[0][3];
    mtx[1][0] += rhs.mtx[1][0], mtx[1][1] += rhs.mtx[1][1], mtx[1][2] += rhs.mtx[1][2], mtx[1][3] += rhs.mtx[1][3];
    mtx[2][0] += rhs.mtx[2][0], mtx[2][1] += rhs.mtx[2][1], mtx[2][2] += rhs.mtx[2][2], mtx[2][3] += rhs.mtx[2][3];
    mtx[3][0] += rhs.mtx[3][0], mtx[3][1] += rhs.mtx[3][1], mtx[3][2] += rhs.mtx[3][2], mtx[3][3] += rhs.mtx[3][3];
    return *this;
}

Matrix4 &Matrix4::operator-=(const Matrix4 &rhs){
    mtx[0][0] -= rhs.mtx[0][0], mtx[0][1] -= rhs.mtx[0][1], mtx[0][2] -= rhs.mtx[0][2], mtx[0][3] -= rhs.mtx[0][3];
    mtx[1][0] -= rhs.mtx[1][0], mtx[1][1] -= rhs.mtx[1][1], mtx[1][2] -= rhs.mtx[1][2], mtx[1][3] -= rhs.mtx[1][3];
    mtx[2][0] -= rhs.mtx[2][0], mtx[2][1] -= rhs.mtx[2][1], mtx[2][2] -= rhs.mtx[2][2], mtx[2][3] -= rhs.mtx[2][3];
    mtx[3][0] -= rhs.mtx[3][0], mtx[3][1] -= rhs.mtx[3][1], mtx[3][2] -= rhs.mtx[3][2], mtx[3][3] -= rhs.mtx[3][3];
    return *this;
}

Matrix4 &Matrix4::operator*=(const Matrix4 &rhs){
    Matrix4 tmp;

    // Row 1.
    tmp.mtx[0][0] = (mtx[0][0] * rhs.mtx[0][0]) + (mtx[0][1] * rhs.mtx[1][0]) + (mtx[0][2] * rhs.mtx[2][0]) + (mtx[0][3] * rhs.mtx[3][0]);
    tmp.mtx[0][1] = (mtx[0][0] * rhs.mtx[0][1]) + (mtx[0][1] * rhs.mtx[1][1]) + (mtx[0][2] * rhs.mtx[2][1]) + (mtx[0][3] * rhs.mtx[3][1]);
    tmp.mtx[0][2] = (mtx[0][0] * rhs.mtx[0][2]) + (mtx[0][1] * rhs.mtx[1][2]) + (mtx[0][2] * rhs.mtx[2][2]) + (mtx[0][3] * rhs.mtx[3][2]);
    tmp.mtx[0][3] = (mtx[0][0] * rhs.mtx[0][3]) + (mtx[0][1] * rhs.mtx[1][3]) + (mtx[0][2] * rhs.mtx[2][3]) + (mtx[0][3] * rhs.mtx[3][3]);

    // Row 2.
    tmp.mtx[1][0] = (mtx[1][0] * rhs.mtx[0][0]) + (mtx[1][1] * rhs.mtx[1][0]) + (mtx[1][2] * rhs.mtx[2][0]) + (mtx[1][3] * rhs.mtx[3][0]);
    tmp.mtx[1][1] = (mtx[1][0] * rhs.mtx[0][1]) + (mtx[1][1] * rhs.mtx[1][1]) + (mtx[1][2] * rhs.mtx[2][1]) + (mtx[1][3] * rhs.mtx[3][1]);
    tmp.mtx[1][2] = (mtx[1][0] * rhs.mtx[0][2]) + (mtx[1][1] * rhs.mtx[1][2]) + (mtx[1][2] * rhs.mtx[2][2]) + (mtx[1][3] * rhs.mtx[3][2]);
    tmp.mtx[1][3] = (mtx[1][0] * rhs.mtx[0][3]) + (mtx[1][1] * rhs.mtx[1][3]) + (mtx[1][2] * rhs.mtx[2][3]) + (mtx[1][3] * rhs.mtx[3][3]);

    // Row 3.
    tmp.mtx[2][0] = (mtx[2][0] * rhs.mtx[0][0]) + (mtx[2][1] * rhs.mtx[1][0]) + (mtx[2][2] * rhs.mtx[2][0]) + (mtx[2][3] * rhs.mtx[3][0]);
    tmp.mtx[2][1] = (mtx[2][0] * rhs.mtx[0][1]) + (mtx[2][1] * rhs.mtx[1][1]) + (mtx[2][2] * rhs.mtx[2][1]) + (mtx[2][3] * rhs.mtx[3][1]);
    tmp.mtx[2][2] = (mtx[2][0] * rhs.mtx[0][2]) + (mtx[2][1] * rhs.mtx[1][2]) + (mtx[2][2] * rhs.mtx[2][2]) + (mtx[2][3] * rhs.mtx[3][2]);
    tmp.mtx[2][3] = (mtx[2][0] * rhs.mtx[0][3]) + (mtx[2][1] * rhs.mtx[1][3]) + (mtx[2][2] * rhs.mtx[2][3]) + (mtx[2][3] * rhs.mtx[3][3]);

    // Row 4.
    tmp.mtx[3][0] = (mtx[3][0] * rhs.mtx[0][0]) + (mtx[3][1] * rhs.mtx[1][0]) + (mtx[3][2] * rhs.mtx[2][0]) + (mtx[3][3] * rhs.mtx[3][0]);
    tmp.mtx[3][1] = (mtx[3][0] * rhs.mtx[0][1]) + (mtx[3][1] * rhs.mtx[1][1]) + (mtx[3][2] * rhs.mtx[2][1]) + (mtx[3][3] * rhs.mtx[3][1]);
    tmp.mtx[3][2] = (mtx[3][0] * rhs.mtx[0][2]) + (mtx[3][1] * rhs.mtx[1][2]) + (mtx[3][2] * rhs.mtx[2][2]) + (mtx[3][3] * rhs.mtx[3][2]);
    tmp.mtx[3][3] = (mtx[3][0] * rhs.mtx[0][3]) + (mtx[3][1] * rhs.mtx[1][3]) + (mtx[3][2] * rhs.mtx[2][3]) + (mtx[3][3] * rhs.mtx[3][3]);

    *this = tmp;
    return *this;
}

Matrix4 &Matrix4::operator*=(float scalar){
    mtx[0][0] *= scalar, mtx[0][1] *= scalar, mtx[0][2] *= scalar, mtx[0][3] *= scalar;
    mtx[1][0] *= scalar, mtx[1][1] *= scalar, mtx[1][2] *= scalar, mtx[1][3] *= scalar;
    mtx[2][0] *= scalar, mtx[2][1] *= scalar, mtx[2][2] *= scalar, mtx[2][3] *= scalar;
    mtx[3][0] *= scalar, mtx[3][1] *= scalar, mtx[3][2] *= scalar, mtx[3][3] *= scalar;
    return *this;
}

Matrix4 &Matrix4::operator/=(float scalar){
    mtx[0][0] /= scalar, mtx[0][1] /= scalar, mtx[0][2] /= scalar, mtx[0][3] /= scalar;
    mtx[1][0] /= scalar, mtx[1][1] /= scalar, mtx[1][2] /= scalar, mtx[1][3] /= scalar;
    mtx[2][0] /= scalar, mtx[2][1] /= scalar, mtx[2][2] /= scalar, mtx[2][3] /= scalar;
    mtx[3][0] /= scalar, mtx[3][1] /= scalar, mtx[3][2] /= scalar, mtx[3][3] /= scalar;
    return *this;
}

Matrix4 Matrix4::operator+(const Matrix4 &rhs) const{
    Matrix4 tmp(*this);
    tmp += rhs;
    return tmp;
}

Matrix4 Matrix4::operator-(const Matrix4 &rhs) const{
    Matrix4 tmp(*this);
    tmp -= rhs;
    return tmp;
}

Matrix4 Matrix4::operator*(const Matrix4 &rhs) const{
    Matrix4 tmp(*this);
    tmp *= rhs;
    return tmp;
}

Matrix4 Matrix4::operator*(float scalar) const{
    Matrix4 tmp(*this);
    tmp *= scalar;
    return tmp;
}

Matrix4 Matrix4::operator/(float scalar) const{
    Matrix4 tmp(*this);
    tmp /= scalar;
    return tmp;
}

void Matrix4::identity(){
    mtx[0][0] = 1.0f, mtx[0][1] = 0.0f, mtx[0][2] = 0.0f, mtx[0][3] = 0.0f;
    mtx[1][0] = 0.0f, mtx[1][1] = 1.0f, mtx[1][2] = 0.0f, mtx[1][3] = 0.0f;
    mtx[2][0] = 0.0f, mtx[2][1] = 0.0f, mtx[2][2] = 1.0f, mtx[2][3] = 0.0f;
    mtx[3][0] = 0.0f, mtx[3][1] = 0.0f, mtx[3][2] = 0.0f, mtx[3][3] = 1.0f;
}

const Matrix4 Matrix4::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f);

void Matrix4::fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees){
    // Constructs a rotation matrix based on a Euler Transform.
    // I use the popular NASA standard airplane convention of 
    // heading-pitch-roll (i.e., RzRxRy).

    headDegrees = Math::degreesToRadians(headDegrees);
    pitchDegrees = Math::degreesToRadians(pitchDegrees);
    rollDegrees = Math::degreesToRadians(rollDegrees);

    float cosH = cosf(headDegrees);
    float cosP = cosf(pitchDegrees);
    float cosR = cosf(rollDegrees);
    float sinH = sinf(headDegrees);
    float sinP = sinf(pitchDegrees);
    float sinR = sinf(rollDegrees);

    mtx[0][0] = cosR * cosH - sinR * sinP * sinH;
    mtx[0][1] = sinR * cosH + cosR * sinP * sinH;
    mtx[0][2] = -cosP * sinH;
    mtx[0][3] = 0.0f;

    mtx[1][0] = -sinR * cosP;
    mtx[1][1] = cosR * cosP;
    mtx[1][2] = sinP;
    mtx[1][3] = 0.0f;

    mtx[2][0] = cosR * sinH + sinR * sinP * cosH;
    mtx[2][1] = sinR * sinH - cosR * sinP * cosH;
    mtx[2][2] = cosP * cosH;
    mtx[2][3] = 0.0f;

    mtx[3][0] = 0.0f;
    mtx[3][1] = 0.0f;
    mtx[3][2] = 0.0f;
    mtx[3][3] = 1.0f;
}

Matrix4 Matrix4::rotateX(float degrees){
    degrees = Math::degreesToRadians(degrees);

    float c = cosf(degrees);
    float s = sinf(degrees);

	Matrix4 matrix = Matrix4(1.0f,0.0f,0.0f,0.0f,
							 0.0f,   c,   s,0.0f,
							 0.0f,  -s,   c,0.0f,
							 0.0f,0.0f,0.0f,1.0f);

	return operator*(matrix);
}

Matrix4 Matrix4::rotateY(float degrees){
    degrees = Math::degreesToRadians(degrees);

    float c = cosf(degrees);
    float s = sinf(degrees);

	Matrix4 matrix = Matrix4(   c,0.0f,  -s,0.0f,
						     0.0f,1.0f,0.0f,0.0f,
						        s,0.0f,   c,0.0f,
						     0.0f,0.0f,0.0f,1.0f);

	return operator*(matrix);
}

Matrix4 Matrix4::rotateZ(float degrees){
    degrees = Math::degreesToRadians(degrees);

    float c = cosf(degrees);
    float s = sinf(degrees);

	Matrix4 matrix = Matrix4(   c,   s,0.0f,0.0f,
							   -s,   c,0.0f,0.0f,
							 0.0f,0.0f,1.0f,0.0f,
						     0.0f,0.0f,0.0f,1.0f);

	return operator*(matrix);
}

Matrix4 Matrix4::translate(float x, float y, float z){
	Matrix4 matrix = Matrix4(1.0f,0.0f,0.0f,0.0f,
							 0.0f,1.0f,0.0f,0.0f,
							 0.0f,0.0f,1.0f,0.0f,
						        x,   y,   z,1.0f);

	return operator*(matrix);
}

Matrix4 Matrix4::scale(float x, float y, float z){
	Matrix4 matrix = Matrix4(   x,0.0f,0.0f,0.0f,
							 0.0f,   y,0.0f,0.0f,
							 0.0f,0.0f,   z,0.0f,
						     0.0f,0.0f,0.0f,1.0f);

	return operator*(matrix);
}

void Matrix4::toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const{
    // Extracts the Euler angles from a rotation matrix. The returned
    // angles are in degrees. This method might suffer from numerical
    // imprecision for ill defined rotation matrices.
    //
    // This function only works for rotation matrices constructed using
    // the popular NASA standard airplane convention of heading-pitch-roll 
    // (i.e., RzRxRy).
    //
    // The algorithm I use here is from a paper written by David Eberly
    // titled "Euler Angle Formulas". This paper can be found on his
    // Magic Software web site (http://www.magic-software.com).

    float thetaX = asinf(mtx[1][2]);
    float thetaY = 0.0f;
    float thetaZ = 0.0f;

    if (thetaX < Math::HALF_PI)
    {
        if (thetaX > -Math::HALF_PI)
        {
            thetaZ = atan2f(-mtx[1][0], mtx[1][1]);
            thetaY = atan2f(-mtx[0][2], mtx[2][2]);
        }
        else
        {
            // Not a unique solution.
            thetaZ = -atan2f(mtx[2][0], mtx[0][0]);
            thetaY = 0.0f;
        }
    }
    else
    {
        // Not a unique solution.
        thetaZ = atan2f(mtx[2][0], mtx[0][0]);
        thetaY = 0.0f;
    }

    headDegrees = Math::radiansToDegrees(thetaY);
    pitchDegrees = Math::radiansToDegrees(thetaX);
    rollDegrees = Math::radiansToDegrees(thetaZ);
}

void Matrix4::lerp(const Matrix4 &matrix){
	for(int column = 0, valuesCounter = 0; column < 4; column++)
		for(int row = 0; row < 4; row++, valuesCounter++)
			mtx[column][row] = mtx[column][row] + 0.15f * (matrix[column][row] - mtx[column][row]);
}