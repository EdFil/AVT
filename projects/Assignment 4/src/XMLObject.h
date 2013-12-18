#ifndef XML_OBJECT_H
#define XML_OBJECT_H

#include "Object.h"

class XMLObject : public Object {

public:
	XMLObject(std::string xmlNodeName) : Object(xmlNodeName){
		parseVertexInfo(xmlNodeName);
		setColor(1.0f, 1.0f, 1.0f, 1.0f);
		vertexToVec3();
	}

	XMLObject(std::string xmlNodeName, glm::vec3 position) : Object(xmlNodeName, position){
		parseVertexInfo(xmlNodeName);
		setColor(1.0f, 1.0f, 1.0f, 1.0f);
		vertexToVec3();
	}

private:
	void parseVertexInfo(std::string objectName);
	void explode(std::string const & s, char delim, float* result);
};
#endif
