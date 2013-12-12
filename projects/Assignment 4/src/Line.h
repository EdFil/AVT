#ifndef LINE_H
#define LINE_H

#include "Object.h"

class Line : public Object {

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

	//Setters
	void setVisible(bool value);
};

#endif
