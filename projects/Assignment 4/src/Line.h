#ifndef LINE_H
#define LINE_H

#include "Object.h"

class Line : public Object {

	static const float LINE_WIDTH;
	static const float LINE_LENGTH;

	const Object *_object;
	glm::vec3 _axis;

	bool _isVisible;

public:
	Line();

	//Virtual functions
	void draw(GLuint* vaoId);
	bool checkIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec3 &outputVec);
	void updateModifiedVertex();

	//Line bind function
	void bindToObject(Object* obj);
	void setToAxis(glm::vec3 axis);

	//Getters
	bool isVisible();

	//Setters
	void setVisible(bool value);
};

#endif
