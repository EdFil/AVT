#ifndef BACK_H
#define BACK_H

#include <cmath>
#include <vector>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Triangle.h"

class Back : public Triangle {

public:
	Back(){
		parseVertexInfo("Back");

		mat4 transformation1 = rotate(-90.0f, vec3(0,0,1));
		mat4 transformation2 = translate(0.0f, 1.0f, 0.0f);
		_transformationMatrix.push_back(
			transformation2 * transformation1 * mat4()
		);

		transformation1 = rotate(-90.0f, vec3(1,0,0));
		transformation2 = rotate(-45.0f, vec3(0,1,0));
		mat4 transformation3 = translate(0.0f, 0.38f, 0.0f);
		_transformationMatrix.push_back(
			transformation3 * transformation2 * transformation1 * mat4()
		);
	}

};
#endif
