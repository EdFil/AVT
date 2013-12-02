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

		mat4 transformation1 = rotate(-135.0f, vec3(0,0,1));
		mat4 transformation2 = translate(-0.3f, 0.5f, -0.1f);
		_transformationMatrix.push_back(
			transformation2 * transformation1 * mat4()
		);

		transformation1 = rotate(-90.0f, vec3(1,0,0));
		transformation2 = rotate(45.0f, vec3(0,1,0));
		mat4 transformation3 = translate(0.29f, 0.43f, -0.29f);
		_transformationMatrix.push_back(
			transformation3 * transformation2 * transformation1 * mat4()
		);
	}

};
#endif
