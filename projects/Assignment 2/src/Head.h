#ifndef HEAD_H
#define HEAD_H

#include <vector>
#include <iostream>

#include "Triangle.h"

class Head : public Triangle {

public:
	Head(){
		parseVertexInfo("Head");

		Matrix* tangram = new Matrix();
		tangram->rotateZ(-135.0f);
		tangram->translate(-0.68f, 0.88f, 0.0f);

		Matrix* square = new Matrix();
		square->rotateZ(135.0f);
		square->translate(0.0f, 0.2f, 0.0f);

		_transformationMatrix.push_back(tangram);
		_transformationMatrix.push_back(square);
	}

};
#endif
