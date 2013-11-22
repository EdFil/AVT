#ifndef TORSO_H
#define TORSO_H

#include <cmath>
#include <vector>
#include <iostream>

#include "Triangle.h"

class Torso : public Triangle {

public:
	Torso(){
		parseVertexInfo("Torso");

		Matrix* tangram = new Matrix();
		tangram->rotateZ(180.0f);
		tangram->translate(0.0f, 0.2f, 0.0f);

		Matrix* square = new Matrix();
		square->rotateZ(-135.0f);
		square->translate(0.0f, 0.2f, 0.0f);

		_transformationMatrix.push_back(tangram);
		_transformationMatrix.push_back(square);
	}

};
#endif
