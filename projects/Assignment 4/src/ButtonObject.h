#ifndef BUTTON_OBJECT_H
#define BUTTON_OBJECT_H

#include "Object.h"

class ButtonObject : public Object {
	
	float _width;
	float _height;
	glm::vec2 _position;

public:

	ButtonObject(std::string name, int textureID, bool selectable, float width, float height, glm::vec2 position);

	//Getters
	

	//Virtual functions
	void draw(GLuint* vaoId);
	void setPrograms();
	void createBufferObjects();
	void saveObject(std::string);
	void createBufferObjects(GLuint*, GLuint*);

	bool checkIntersection(glm::vec2);
	bool checkIntersection(glm::vec3, glm::vec3, glm::vec3 &);
};

#endif
