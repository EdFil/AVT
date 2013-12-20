#ifndef OBJ_OBJECT_H
#define OBJ_OBJECT_H

#include "Object.h"

class ObjObject : public Object {

	std::string _objFileDir;

public:

	ObjObject(std::string fileName);
	ObjObject(std::string, std::string fileName);

	//Getters
	std::string getObjFileDir();

	//Virtual functions
	void draw(GLuint* vaoId);
	void setPrograms();
	void saveObject(std::string);


private:
	void loadMesh(const char* fileName);
	std::vector<std::string> explode(const std::string &string, char delim);
	
};

#endif
