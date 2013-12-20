#ifndef XML_OBJECT_H
#define XML_OBJECT_H

#include "Object.h"
#include "ObjectManager.h"

class XMLLoader {

	ObjectManager* _objectManager;
	std::string _filename;

public:
	XMLLoader(std::string, ObjectManager*);
	
private:
	void loadGame(std::string);
	void explode(std::string const & s, char delim, float* result);
};
#endif