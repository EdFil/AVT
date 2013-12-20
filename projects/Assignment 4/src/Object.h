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

class Object {

	static const glm::vec3 DEFAULT_POSITION;
	static const glm::quat DEFAULT_ROTATION;
	static const glm::vec3 DEFAULT_SCALE;

public:
	
	typedef struct {
		float XYZW[4];
		float NORMAL[4];
		float UV[2];
	} Vertex;

	typedef struct {
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;
	} Properties;

protected:
	std::string _name;
	float _color[4];
	ShaderManager *_shaderManager;
	GLuint _vaoId;
	GLuint _vboId;
	bool _selected;
	bool _selectable;
	int _currentPropertyIndex;

	bool _loop;
	int _lerpStartTime;
	int _timeToRun;
	int _lerpFrom;
	int _lerpTo;
	glm::mat4 _lerpedModelMatrix;

	int _textureID;
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
    virtual void createBufferObjects(GLuint* vaoId, GLuint* vboId) = 0;
	virtual void draw(GLuint* vaoId) = 0;
	virtual bool checkIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec3 &outputVec);
	virtual void updateModifiedVertex();
	virtual void setPrograms() = 0;
	
	//Animation Functions
	void addProperty();
	void removeProperty();
	void nextProperty();
	void prevProperty();
	void calculateModelMatrix();
	void lerpModelMatrix(float alpha);
	void lerpProperties(int index1, int index2, int time);

	//Selecting functions
	void select();
	void unselect();
	void setAsNonSelectable();
	void setAsSelectable();

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
	void setColor(const float color[4]);
	void setColor(const float r, const float g, const float b, const float a);
	void setShaderManager(ShaderManager *shaderManager);
	void setTexture(const int id);
	void setLoop(bool value);


	//Debug
	void printPropertyArray(int);

	//Save
	virtual void saveObject(std::string) = 0;


protected:
	void vertexToVec3();
	
};

#endif


