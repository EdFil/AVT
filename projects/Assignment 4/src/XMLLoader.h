#ifndef XML_OBJECT_H
#define XML_OBJECT_H

#include "Object.h"
#include "ObjectManager.h"

class XMLLoader {

	ObjectManager* _objectManager;

public:

	XMLLoader();
	XMLLoader(ObjectManager*);

	void loadGame(std::string);

private:
	void explode(std::string const & s, char delim, float* result);
};
#endif