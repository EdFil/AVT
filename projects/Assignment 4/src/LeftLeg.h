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
		_name = "LeftLeg";

		mat4 transformation1 = translate(-0.2f, 0.0f, 0.1f);
		_transformationMatrix.push_back(
			transformation1 * mat4()
		);

		transformation1 = rotate(-90.0f, vec3(1,0,0));
		mat4 transformation2 = rotate(45.0f, vec3(0,1,0));
		mat4 transformation3 = translate(-0.56f, 0.45f, 0.57f);
		_transformationMatrix.push_back(
			transformation3 * transformation2 * transformation1 * mat4()
		);
	}

};
#endif
