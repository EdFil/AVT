#ifndef HEAD_H
#define HEAD_H

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Triangle.h"

using namespace glm;

class Head : public Triangle {

public:
	Head(){
		parseVertexInfo("Head");
		_name = "Head";

		mat4 tangram = mat4();
		mat4 transformation1 = rotate(-135.0f, vec3(0,0,1));
		mat4 transformation2 = translate(-0.68f, 1.68f, 0.05f);
		_transformationMatrix.push_back(
			transformation2 * transformation1 * mat4()
		);

		transformation1 = rotate(-90.0f, vec3(1,0,0));
		transformation2 = rotate(135.0f, vec3(0,1,0));
		mat4 transformation3 = translate(0.0f, 0.42f, 0.0f);
		_transformationMatrix.push_back(
			transformation3 * transformation2 * transformation1 * mat4()
		);
	}

};
#endif
