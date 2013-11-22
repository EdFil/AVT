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

		Matrix4 tangram = Matrix4::IDENTITY;
		tangram = tangram.translate(-0.8f, 1.0f, -0.03f);

		Matrix4 square = Matrix4::IDENTITY;
		square = square.rotateY(45.0f);

		_transformationMatrix.push_back(tangram);
		_transformationMatrix.push_back(square);
	}

};
#endif
