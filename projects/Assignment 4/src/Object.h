#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <iostream>
#include <Vector>
#include "glm\glm.hpp"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "glm\gtx\intersect.hpp"
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

#define VERTICES 0
#define COLORS 1

class Object {

	static const glm::vec3 DEFAULT_POSITION;
	static const glm::quat DEFAULT_ROTATION;
	static const glm::vec3 DEFAULT_SCALE;

protected:
	
	typedef struct {
		float XYZW[4];
		float RGBA[4];
	} Vertex;

	typedef struct {
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;
	} Properties;

	char* _name;
	GLuint _vaoId;
	GLuint _vboId;
	bool _selected;
	int _currentPropertyIndex;
	std::vector<Vertex> _vertexArray;
	std::vector<Properties> _propertiesArray;
	glm::mat4 _currentModelMatrix;

public:
	Object(char* name);


	//Virtual Functions
    virtual void createBufferObjects(GLuint* vaoId, GLuint* vboId);
	virtual void draw(GLuint uniformId, GLuint* vaoId);
	
	//Animation Functions
	void addProperty();
	void removeProperty();
	void nextProperty();
	void prevProperty();

	//Selecting functions
	virtual bool checkIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec3 &outputVec);

	//Moving functions
	void translate(float, float, float);
	void rotate(float,glm::vec3);
	void scale(float, float, float);

	//Setters
	void setVaoId(int value);
	void setVboId(int value);


private:
	glm::vec3 vertexToVec3(const Vertex &vertex);
	void calculateModelMatrix();
	
};

#endif


