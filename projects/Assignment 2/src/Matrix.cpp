#include <iostream>
#include <string.h>
#include <cmath>

#include "Matrix.h"

Matrix::Matrix() : _numRows(4), _numColumns(4){
	alloc();
	for(int i = 0; i < _numColumns; i++)
		_matrix[i][i] = 1.0f;
}

Matrix::Matrix(const Matrix* matrixToCopy): _numRows(matrixToCopy->getNumRows()), _numColumns(matrixToCopy->getNumColumns()){
	alloc();
	for(int column = 0; column < _numColumns; column++)
		for(int row = 0; row < _numRows; row++)
			_matrix[column][row] = matrixToCopy->getValue(column, row);
}

Matrix::Matrix(int numColumns, int numRows, float value): _numRows(numRows), _numColumns(numColumns){
	alloc();
	fill(value);
}

Matrix::Matrix(int numColumns, int numRows, float values[]): _numRows(numRows), _numColumns(numColumns){
	alloc();
	for(int column = 0, valuesCounter = 0; column < _numColumns; column++)
		for(int row = 0; row < _numRows; row++, valuesCounter++)
			_matrix[column][row] = values[valuesCounter];
}

void Matrix::fill(float valueToFillWith){
	for(int column = 0; column < _numColumns; column++)
		for(int row = 0; row < _numRows; row++)
			_matrix[column][row] = valueToFillWith;
}

Matrix* Matrix::operator=(Matrix* rhs){
	return new Matrix(rhs);
}

Matrix* Matrix::operator+(Matrix* rhs){
	Matrix *result = new Matrix(rhs);
	for(int column = 0; column < _numColumns; column++)
		for(int row = 0; row < _numRows; row++)
			result->setValue(column, row, _matrix[column][row] + rhs->getValue(column, row));
	return result;
}

Matrix* Matrix::operator-(Matrix* rhs){
	Matrix *result = new Matrix(rhs);
	for(int column = 0; column < _numColumns; column++)
		for(int row = 0; row < _numRows; row++)
			result->setValue(column, row, _matrix[column][row] - rhs->getValue(column, row));
	return result;
}

Matrix* Matrix::operator*(Matrix* rhs){
	Matrix *result = new Matrix(this->getNumColumns(), rhs->getNumRows(), 0.0f);
	for(int column = 0; column < result->getNumColumns(); column++)
		for(int row = 0; row <  result->getNumRows(); row++)
			for (int inner = 0; inner < this->getNumRows(); inner++) {
                result->setValue(column, row, result->getValue(column, row) + this->getValue(inner, row) * rhs->getValue(column, inner));
            }
	return result;
}

void Matrix::translate(float x, float y, float z){
	_matrix[0][3] += x;
	_matrix[1][3] += y;
	_matrix[2][3] += z;
}

void Matrix::rotateZ(float z){
	float cosine = (float) cos(z * PI / 180.0);
	float sine = (float) sin(z * PI / 180.0);
	float rotationArray[16] = {
		   cosine,  -sine,  0.0f,  0.0f,
		     sine, cosine,  0.0f,  0.0f,
		     0.0f,   0.0f,  1.0f,  0.0f,
		     0.0f,   0.0f,  0.0f,  1.0f
		}; // Row Major (GLSL is Column Major)
	Matrix* matrix = new Matrix(4,4,rotationArray);
	Matrix* result = operator*(matrix);
	setMatrix(result);
}

void Matrix::scale(float x, float y, float z){
	float scaleArray[16] = {
		        x,  0.0f,  0.0f,  0.0f,
		     0.0f,     y,  0.0f,  0.0f,
		     0.0f,   0.0f,    z,  0.0f,
		     0.0f,   0.0f,  0.0f,  1.0f
		}; // Row Major (GLSL is Column Major)
	Matrix* matrix = new Matrix(4,4,scaleArray);
	Matrix* result = operator*(matrix);
	setMatrix(result);
}

void Matrix::print(){
	for(int column = 0; column < _numColumns; column++){
		std::cout << "|"; 
		for(int row = 0; row < _numRows; row++)
			std::cout << _matrix[column][row] << ((row != _numRows-1)?", ":""); 
		std::cout << "|" << std::endl;
	}
	std::cout << "(" << _numColumns << "x" << _numRows << ")" << std::endl; 
 }

float* Matrix::toArray(){
	int matrixSize = getNumRows() * getNumColumns();
	float* array = new float[matrixSize];
	for(int column = 0, valuesCounter = 0; column < _numColumns; column++)
		for(int row = 0; row < _numRows; row++, valuesCounter++)
			array[valuesCounter] = _matrix[column][row];
	return array;
}

void Matrix::alloc(){
	_matrix.resize(_numColumns);
		for(int i = 0; i < _numColumns; i++)
			_matrix[i].resize(_numRows);
}

void Matrix::lerp(Matrix* matrix){
	for(int column = 0, valuesCounter = 0; column < _numColumns; column++)
		for(int row = 0; row < _numRows; row++, valuesCounter++)
			_matrix[column][row] = _matrix[column][row] + 0.08f * (matrix->getValue(column, row) - _matrix[column][row]);
}

void Matrix::setMatrix(Matrix* matrixToCopy){
	for(int column = 0; column < _numColumns; column++)
		for(int row = 0; row < _numRows; row++)
			_matrix[column][row] = matrixToCopy->getValue(column, row);
}