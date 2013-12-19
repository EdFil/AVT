#include "XMLObject.h"
#include <rapidxml.hpp>
#include <fstream>
#include <sstream>

XMLObject::XMLObject(std::string xmlNodeName) : Object(xmlNodeName){
	parseVertexInfo(xmlNodeName);
	vertexToVec3();
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
}

XMLObject::XMLObject(std::string xmlNodeName, glm::vec3 position) : Object(xmlNodeName, position){
	parseVertexInfo(xmlNodeName);
	vertexToVec3();
	setColor(1.0f, 1.0f,0.0f, 1.0f);
}

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

void XMLObject::setPrograms(){
	_programsToUse.push_back(_shaderManager->getProgram("NormalShader"));
	_programsToUse.push_back(_shaderManager->getProgram("SelectedShader"));
}