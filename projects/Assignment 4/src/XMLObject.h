#ifndef XML_OBJECT_H
#define XML_OBJECT_H

#include "Object.h"

class XMLObject : public Object {

public:
	XMLObject(std::string xmlNodeName);
	XMLObject(std::string xmlNodeName, glm::vec3 position);


	void draw(GLuint *vaoId);
	void setPrograms();

private:
	void parseVertexInfo(std::string objectName);
	void explode(std::string const & s, char delim, float* result);
};
#endif
