#ifndef LEFT_LEG_H
#define LEFT_LEG_H

#include <cmath>
#include <vector>
#include <iostream>

#include "Square.h"

class LeftLeg : public Square {

public:
	LeftLeg(){
		parseVertexInfo("LeftLeg");

		Matrix* tangram = new Matrix();
		tangram->scale(-1.0f, 1.0f, 1.0f);
		tangram->rotateZ(90.0f);
		tangram->translate(0.4f, -0.2f, 0.0f);

		Matrix* square = new Matrix();
		square->rotateZ(45.0f);
		square->translate(-0.565f, -0.37f, 0.0f);

		_transformationMatrix.push_back(tangram);
		_transformationMatrix.push_back(square);
	}

};
#endif
