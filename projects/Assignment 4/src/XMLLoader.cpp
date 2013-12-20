#include "XMLLoader.h"
#include "ObjObject.h"
#include "TextureManager.h"
#include <glm/gtc/type_ptr.hpp>
#include <rapidxml.hpp>
#include <fstream>
#include <sstream>

XMLLoader::XMLLoader(){}

XMLLoader::XMLLoader(ObjectManager* objectManager){
	_objectManager = objectManager;
}

void XMLLoader::explode(std::string const & s, char delim, float* result){
	int i = 0;
    std::istringstream iss(s);
    for (std::string token; std::getline(iss, token, delim);)
        result[i++] = (float) ::atof(&token[0]);
}

void XMLLoader::loadGame(std::string filename){
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * root_node;
	// Read the xml file into a vector
	std::ifstream theFile (filename);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("Scene");
	// Iterate over the brewerys
	for(rapidxml::xml_node<> * object_node = root_node->first_node("Object"); object_node; object_node = object_node->next_sibling()){
		std::string objFileDir = object_node->first_attribute("objFileDir")->value();
		glm::vec4 color = glm::vec4();
		explode(object_node->first_attribute("color")->value(), ',', &color[0]);
		std::string name = object_node->first_attribute("name")->value();
		int textureID = atoi(object_node->first_attribute("texture")->value());
		bool selectable = atoi(object_node->first_attribute("texture")->value());
		std::vector<Object::Properties> propertiesArray;
		for (rapidxml::xml_node<> * frame_node = object_node->first_node("Frame"); frame_node; frame_node = frame_node->next_sibling()){
			glm::vec3 positionValue = glm::vec3();
			explode(frame_node->first_attribute("position")->value(), ',', &positionValue[0]);
			glm::quat rotationValue = glm::quat();
			explode(frame_node->first_attribute("rotation")->value(), ',', &rotationValue[0]);
			glm::vec3 scaleValue = glm::vec3();
			explode(frame_node->first_attribute("scale")->value(), ',', &scaleValue[0]);
			Object::Properties property;
			memcpy(&property.position[0], &positionValue[0], sizeof(float)*3);
			memcpy(&property.rotation[0], &rotationValue[0], sizeof(float)*4);
			memcpy(&property.scale[0], &scaleValue[0], sizeof(float)*3);
			propertiesArray.push_back(property);
		}
		_objectManager->addObject(new ObjObject(objFileDir, color, name, textureID, selectable, propertiesArray));
	}
}