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

		Matrix4 tangram = Matrix4::IDENTITY;
		tangram = tangram.rotateZ(-135.0f);
		tangram = tangram.translate(-0.3f, 0.5f, -0.1f);

		Matrix4 square = Matrix4::IDENTITY;
		square = square.rotateX(-90.0f);
		square = square.rotateY(45.0f);
		square = square.translate(0.29f, 0.43f, -0.29f);

		_transformationMatrix.push_back(tangram);
		_transformationMatrix.push_back(square);
	}

};
#endif
