#ifndef XML_OBJECT_H
#define XML_OBJECT_H

#include "Object.h"

class XMLObject : public Object {

public:
	XMLObject(char* xmlNodeName) : Object(xmlNodeName){
		parseVertexInfo(xmlNodeName);
		vertexToVec3();
	}

	XMLObject(char* xmlNodeName, glm::vec3 position) : Object(xmlNodeName, position){
		parseVertexInfo(xmlNodeName);
		vertexToVec3();
	}

private:
	void parseVertexInfo(char* objectName);
	void explode(std::string const & s, char delim, float* result);
};
#endif
