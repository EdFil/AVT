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
		_name = "Neck";

		/*mat4 transformation1 = translate(-0.8f, 1.0f, -0.03f);
		_transformationMatrix.push_back(
			transformation1 * mat4()
		);

		transformation1 = rotate(45.0f, vec3(0,1,0));
		_transformationMatrix.push_back(
			transformation1 * mat4()
		);*/
		_transformationMatrix.push_back(mat4());
	}

};
#endif
