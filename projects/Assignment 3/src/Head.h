#ifndef HEAD_H
#define HEAD_H

#include <vector>
#include <iostream>

#include "Triangle.h"

class Head : public Triangle {

public:
	Head(){
		parseVertexInfo("Head");

		Matrix4 tangram = Matrix4::IDENTITY;
		tangram = tangram.rotateZ(-135.0f);
		tangram = tangram.translate(-0.68f, 1.68f, 0.05f);

		Matrix4 square = Matrix4::IDENTITY;
		square = square.rotateX(-90.0f);
		square = square.rotateY(135.0f);
		square = square.translate(0.0f, 0.42f, 0.0f);

		_transformationMatrix.push_back(tangram);
		_transformationMatrix.push_back(square);
	}

};
#endif
