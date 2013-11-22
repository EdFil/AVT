#ifndef NECK_H
#define NECK_H

#include <cmath>
#include <vector>
#include <iostream>

#include "Square.h"

class Neck : public Square {

public:
	Neck(){
		parseVertexInfo("Neck");

		Matrix* tangram = new Matrix();
		tangram->translate(-0.8f, 0.2f, 0.0f);

		Matrix* square = new Matrix();
		square->rotateZ(-45.0f);
		square->translate(-0.28f, 0.48f, 0.0f);

		_transformationMatrix.push_back(tangram);
		_transformationMatrix.push_back(square);
	}

};
#endif
