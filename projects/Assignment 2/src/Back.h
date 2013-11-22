#ifndef BACK_H
#define BACK_H

#include <cmath>
#include <vector>
#include <iostream>

#include "Triangle.h"

class Back : public Triangle {

public:
	Back(){
		parseVertexInfo("Back");

		Matrix* tangram = new Matrix();
		tangram->rotateZ(-90.0f);
		tangram->translate(0.0f, 0.2f, 0.0f);

		Matrix* square = new Matrix();
		square->rotateZ(-45.0f);
		square->translate(0.0f, 0.2f, 0.0f);

		_transformationMatrix.push_back(tangram);
		_transformationMatrix.push_back(square);
	}

};
#endif
