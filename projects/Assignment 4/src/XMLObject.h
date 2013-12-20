#ifndef XML_OBJECT_H
#define XML_OBJECT_H

#include "Object.h"

class XMLObject : public Object {


public:
	XMLObject(std::string xmlNodeName);

	XMLObject(std::string filename, bool ola) : Object("bary"){
		loadGame(filename);
		vertexToVec3();
		setColor(1.0f, 1.0f, 1.0f, 1.0f);
	}

	XMLObject(std::string xmlNodeName, glm::vec3 position);

	void draw (GLuint*);
	void setPrograms();


private:
	void loadGame(std::string);
	void parseVertexInfo(std::string objectName);
	void explode(std::string const & s, char delim, float* result);
};
#endif
