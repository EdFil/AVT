#include "Object.h"
#include "rapidxml.hpp"
#include <fstream>
#include <sstream>

using namespace glm;

Object::Object() : _matrixToUse(0){
	_selected = false;
	_order = TransformationOrder::UP;
}

bool Object::checkIntersection(vec3 rayOrigin, vec3 rayDir){
	for(int i = 0; i<_modifiedVertexArray.size(); i+=3){
		if(intersectLineTriangle(rayOrigin, rayDir, _modifiedVertexArray[i], _modifiedVertexArray[i+1], _modifiedVertexArray[i+2], vec3(0,0,0))){
			printf("Colided with %s.\n" , _name);
			return true;
		}
	}
	return false;
}

Object::Vertex* Object::parseVertexInfo(char* objectName){
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * root_node;
	// Read the xml file into a vector
	std::ifstream theFile ("../src/VertexInfo.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("Object")->first_node(objectName);
	// Iterate over the brewerys
	for (rapidxml::xml_node<> * vertex_node = root_node->first_node("VertexInfo"); vertex_node; vertex_node = vertex_node->next_sibling())
	{
		float positionValue[4];
		explode(vertex_node->first_attribute("position")->value(), ',', positionValue);
		float colorValue[4];
		explode(vertex_node->first_attribute("color")->value(), ',', colorValue);
		Vertex vertex = {{positionValue[0], positionValue[1], positionValue[2], positionValue[3]},
						 {colorValue[0], colorValue[1], colorValue[2], colorValue[3]}};
		_vertexArray.push_back(vertex);
	}
	return &_vertexArray[0];
}


void Object::explode(std::string const & s, char delim, float* result){
	int i = 0;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim);)
        result[i++] = (float) ::atof(&token[0]);
}