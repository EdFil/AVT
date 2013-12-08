#ifndef XML_OBJECT_H
#define XML_OBJECT_H

#include "Object.h"

class XMLObject : public Object {

public:
	XMLObject(char* xmlNodeName) : Object(xmlNodeName){
		parseVertexInfo(xmlNodeName);
	}

private:
	void parseVertexInfo(char* objectName);
	void explode(std::string const & s, char delim, float* result);
};
#endif
