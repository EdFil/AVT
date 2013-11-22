#ifndef RIGHT_LEG_H
#define RIGHT_LEG_H

#include <cmath>
#include <vector>
#include <iostream>

#include "Triangle.h"

class RightLeg : public Triangle {

public:
	RightLeg(){
		parseVertexInfo("RightLeg");

		Matrix* tangram = new Matrix();
		tangram->rotateZ(-135.0f);
		tangram->translate(-0.3f, -0.3f, 0.0f);

		Matrix* square = new Matrix();
		square->rotateZ(45.0f);
		square->translate(0.28f, 0.48f, 0.0f);

		_transformationMatrix.push_back(tangram);
		_transformationMatrix.push_back(square);
	}

};
#endif
