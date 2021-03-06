#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "ShaderManager.h"
#include "Program.h"
#include <iostream>
#include <Vector>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <glm\gtx\intersect.hpp>
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

	std::string _name;
	ShaderManager *_shaderManager;
	GLuint _vaoId;
	GLuint _vboId;
	bool _selected;
	int _currentPropertyIndex;
	std::vector<Program*> _programsToUse;
	std::vector<Vertex> _vertexArray;
	std::vector<glm::vec3> _modifiedVertexArray;
	std::vector<Properties> _propertiesArray;
	glm::mat4 _currentModelMatrix;


public:
	Object(std::string name);
	Object(std::string name, glm::vec3 position);
	Object(std::string name, glm::vec3 position, glm::vec3 rotarion);
	Object(std::string name, glm::vec3 position, glm::vec3 rotarion, glm::vec3 scale);


	//Virtual Functions
    virtual void createBufferObjects(GLuint* vaoId, GLuint* vboId);
	virtual void draw(GLuint* vaoId);
	virtual bool checkIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec3 &outputVec);
	virtual void updateModifiedVertex();
	
	//Animation Functions
	void addProperty();
	void removeProperty();
	void nextProperty();
	void prevProperty();

	//Selecting functions
	void select();
	void unselect();

	//Moving functions
	void translate(float, float, float);
	void rotate(float,glm::vec3);
	void scale(float, float, float);

	//Getters
	glm::vec3 getPosition() const;
	glm::quat getRotation() const;
	glm::vec3 getScale() const;
	std::string getName() const;
	int getCurrentPropertyIndex() const;
	int getPropertiesArraySize() const;

	//Setters
	void setVaoId(int value);
	void setVboId(int value);
	void setShaderManager(ShaderManager *shaderManager);
	void setPrograms();

protected:
	void vertexToVec3();
	void calculateModelMatrix();
	
};

#endif


