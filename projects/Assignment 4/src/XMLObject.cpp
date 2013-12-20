#include "XMLObject.h"
#include <rapidxml.hpp>
#include <fstream>
#include <sstream>

void XMLObject::parseVertexInfo(std::string objectName){
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * root_node;
	// Read the xml file into a vector
	std::ifstream theFile ("../src/VertexInfo.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	const char* charName = &objectName[0];
	root_node = doc.first_node("Object")->first_node(charName);
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
}

void XMLObject::explode(std::string const & s, char delim, float* result){
	int i = 0;
    std::istringstream iss(s);
    for (std::string token; std::getline(iss, token, delim);)
        result[i++] = (float) ::atof(&token[0]);
}

void XMLObject::loadGame(std::string filename){
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
	for(rapidxml::xml_node<> * vertex_node = root_node->first_node("Object"); vertex_node; vertex_node = vertex_node->next_sibling()){
		for (rapidxml::xml_node<> * vertex_node2 = vertex_node->first_node("VertexInfo"); vertex_node2; vertex_node2 = vertex_node2->next_sibling())
		{
			if(vertex_node2 -> next_sibling() -> name() == "Frame");
			break;
//				break;
			float positionValue[4];
			explode(vertex_node2->first_attribute("position")->value(), ',', positionValue);
			float colorValue[4];
			explode(vertex_node2->first_attribute("color")->value(), ',', colorValue);
			Vertex vertex = {{positionValue[0], positionValue[1], positionValue[2], positionValue[3]},
							 {colorValue[0], colorValue[1], colorValue[2], colorValue[3]}};
			_vertexArray.push_back(vertex);

		}
		for (rapidxml::xml_node<> * vertex_node2 = vertex_node->first_node("Frame"); vertex_node2; vertex_node2 = vertex_node2->next_sibling())
		{
			float scaleValue[3];
			explode(vertex_node2->first_attribute("scale")->value(), ',', scaleValue);
			float rotationValue[4];
			explode(vertex_node2->first_attribute("rotation")->value(), ',', rotationValue);
			float positionValue[3];
			explode(vertex_node2->first_attribute("position")->value(), ',', positionValue);

			Properties properties = {	
												glm::vec3(scaleValue[0], scaleValue[1], scaleValue[2]),
												glm::quat(rotationValue[0], rotationValue[1], rotationValue[2], rotationValue[3]),
												glm::vec3(positionValue[0], positionValue[1], positionValue[2])
											};

			_propertiesArray.push_back(properties);
		}
	}
}