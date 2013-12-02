#ifndef TAIL_H
#define TAIL_H

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Triangle.h"

class Tail : public Triangle {

public:
	Tail(){
		parseVertexInfo("Tail");

		mat4 transformation1 = rotate(90.0f, vec3(0,0,1));
		mat4 transformation2 = translate(0.8f, 1.0f, -0.1f);
		_transformationMatrix.push_back(
			transformation2 * transformation1 * mat4()
		);

		transformation1 = rotate(-90.0f, vec3(1,0,0));
		transformation2 = rotate(-90.0f, vec3(0,1,0));
		mat4 transformation3 = translate(-0.58f, 0.33f, -0.58f);
		_transformationMatrix.push_back(
			transformation3 * transformation2 * transformation1 * mat4()
		);
	}

};
#endif
