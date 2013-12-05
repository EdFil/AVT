#ifndef TORSO_H
#define TORSO_H

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


#include "Triangle.h"

using namespace glm;

class Torso : public Triangle {

public:
	Torso(){
		parseVertexInfo("Torso");
		_name = "Torso";

		mat4 transformation1 = rotate(180.0f, vec3(0,0,1));
		mat4 transformation2 = translate(0.0f, 0.98f, 0.02f);
		_transformationMatrix.push_back(
			transformation2 * transformation1 * mat4()
		);

		transformation1 = rotate(-90.0f, vec3(1,0,0));
		transformation2 = rotate(-135.0f, vec3(0,1,0));
		mat4 transformation3 = translate(0.0f, 0.4f, 0.0f);
		_transformationMatrix.push_back(
			transformation3 * transformation2 * transformation1 * mat4()
		);

		//mat4 transformation1 = translate(0.2f, 0.0f, 0.0f);
		//mat4 mat1 = transformation1;
		//mat4 mat2 = mat1 * transformation1;
		//mat4 mat3 = mat2 * transformation1;
		//mat4 matt4 = mat3 * transformation1;
		//mat4 mat5 = matt4 * transformation1;
		//mat4 mat6 = mat5 * transformation1;
		//_transformationMatrix.push_back(mat1);
		//_transformationMatrix.push_back(mat2);
		//_transformationMatrix.push_back(mat3);
		//_transformationMatrix.push_back(matt4);
		//_transformationMatrix.push_back(mat5);
		//_transformationMatrix.push_back(mat6);
	}

};
#endif
