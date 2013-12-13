#ifndef OBJ_OBJECT_H
#define OBJ_OBJECT_H

#include "Object.h"

class ObjObject : public Object {

public:

	ObjObject(std::string fileName);
	ObjObject(std::string, std::string fileName);

private:
	void loadMesh(const char* fileName);
	std::vector<std::string> explode(const std::string &string, char delim);
	
};

#endif
