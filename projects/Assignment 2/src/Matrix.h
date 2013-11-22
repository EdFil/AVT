#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

#define PI 3.14159265

class Matrix
{
	std::vector<std::vector<float>> _matrix;
	int _numColumns, _numRows;
public:
	Matrix::Matrix();
	Matrix::Matrix(int numColumns, int numRows, float value);
	Matrix::Matrix(int numColumns, int numRows, float values[]);
	Matrix::Matrix(const Matrix* matrixToCopy);

	int getNumColumns() const { return _numColumns; };
	int getNumRows() const { return _numRows; };
	float getValue(int column, int row) const { return _matrix[column][row]; };
	void setValue(int column, int row, float newValue) { _matrix[column][row] = newValue; }

	Matrix* operator=(Matrix* rhs);
	Matrix* operator+(Matrix* rhs);
	Matrix* operator-(Matrix* rhs);
	Matrix* operator*(Matrix* rhs);
	
	
	void lerp(Matrix* matrix);

	void translate(float x, float y, float z);
	void rotateZ(float z);
	void scale(float x, float y, float z);

	float* toArray();
	void print();

private:
	std::vector<std::vector<float>>* getMatrix() { return &_matrix; }
	void setMatrix(Matrix* matrix);
	void alloc(void);
	void fill(float valueToFillWith);
};
#endif
