#ifndef TAIL_H
#define TAIL_H

#include <vector>
#include <iostream>

#include "Triangle.h"

class Tail : public Triangle {

public:
	Tail(){
		parseVertexInfo("Tail");

		Matrix* tangram = new Matrix();
		tangram->rotateZ(90.0f);
		tangram->translate(0.8f, 0.2f, 0.0f);

		Matrix* square = new Matrix();
		square->rotateZ(-90.0f);
		square->translate(-0.565f, 0.761f, 0.0f);

		_transformationMatrix.push_back(tangram);
		_transformationMatrix.push_back(square);
	}

};
#endif
