#include "ObjObject.h"
#include "TextureManager.h"
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

ObjObject::ObjObject(std::string fileName) : Object("null"){
	_objFileDir = fileName;
	std::vector<std::string> path = explode(fileName, '/');
	_name = explode(path[path.size()-1], '.')[0];
	setColor(0.2f, 0.2f, 0.2f, 1.0f);
	loadMesh(fileName.c_str());
}

ObjObject::ObjObject(std::string name, std::string fileName) : Object(name){
	_objFileDir = fileName;
	loadMesh(fileName.c_str());
	setColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void ObjObject::setPrograms(){
	_programsToUse.push_back(_shaderManager->getProgram("NormalShader"));
	_programsToUse.push_back(_shaderManager->getProgram("SelectedShader"));
}

std::string ObjObject::getObjFileDir(){
	return _objFileDir;
}

void ObjObject::draw(GLuint* vaoId) {
	TextureProgram* program;
	if(_selected)
		program = ((TextureProgram*)_programsToUse[1]);
	else
		program = ((TextureProgram*)_programsToUse[0]);
	program->bind();
	glBindVertexArray(vaoId[_vaoId]);
	glUniformMatrix4fv(program->getModelMatrixUniformId(), 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
	glUniform4fv(program->getColorUniformId(), 1, _color);
	if(TextureManager::Inst()->BindTexture(_textureID))
		glUniform1i(program->getTextureUniformId(), 0);
	glDrawArrays(GL_TRIANGLES,0,_vertexArray.size());
	glUseProgram(0);
}

void ObjObject::loadMesh(const char* fileName){
        std::string line = std::string();
        std::ifstream file(fileName);

		//Temporary arrays to store loaded information
        std::vector<glm::vec4> vertices, normals;
		std::vector<glm::vec2> uvs;
        
        if (file.is_open()) {
                while (getline(file, line)) {
					std::vector<std::string> splitedLine = explode(line, ' ');
					if(splitedLine.size() > 0){
						if(splitedLine[0] == "#"){
							continue; //Comment in obj, skip this line
						}
						else if(splitedLine[0] == "v"){ //Ex line => v 1.00000 0.45555 1.10000
							float x = atof(splitedLine[1].c_str());
							float y = atof(splitedLine[2].c_str());
							float z = atof(splitedLine[3].c_str());
							vertices.push_back(glm::vec4(x,y,z,1.0f));
						}
						else if(splitedLine[0] == "vt"){ //Ex line => vt 1.00000 0.45555
							float x = atof(splitedLine[1].c_str());
							float y = atof(splitedLine[2].c_str());
							uvs.push_back(glm::vec2(x,y));
						}
						else if(splitedLine[0] == "vn"){ //Ex line => vn 1.00000 0.45555 0.65555
							float x = atof(splitedLine[1].c_str());
							float y = atof(splitedLine[2].c_str());
							float z = atof(splitedLine[3].c_str());
							normals.push_back(glm::vec4(x,y,z,1.0f));
						}
						else if(splitedLine[0] == "f"){ 
							Vertex vertex1, vertex2, vertex3;
							std::vector<std::string> face1 = explode(splitedLine[1], '/');
							std::vector<std::string> face2 = explode(splitedLine[2], '/');
							std::vector<std::string> face3 = explode(splitedLine[3], '/');
							//Copy vertex information from temporary vertices array to vertices
							memcpy(vertex1.XYZW, &vertices[atoi(face1[0].c_str())-1][0], sizeof(vertex1.XYZW));
							memcpy(vertex2.XYZW, &vertices[atoi(face2[0].c_str())-1][0], sizeof(vertex2.XYZW));
							memcpy(vertex3.XYZW, &vertices[atoi(face3[0].c_str())-1][0], sizeof(vertex3.XYZW));
							if((face1.size() > 1) && face1[1].size() > 0){
								//UV information
								memcpy(vertex1.UV, &uvs[atoi(face1[1].c_str())-1][0], sizeof(vertex1.UV));
								memcpy(vertex2.UV, &uvs[atoi(face2[1].c_str())-1][0], sizeof(vertex2.UV));
								memcpy(vertex3.UV, &uvs[atoi(face3[1].c_str())-1][0], sizeof(vertex3.UV));
							}
							if((face1.size() > 2) && face1[2].size() > 0){
								//Normal information
								memcpy(vertex1.NORMAL, &normals[atoi(face1[2].c_str())-1][0], sizeof(vertex1.NORMAL));
								memcpy(vertex2.NORMAL, &normals[atoi(face2[2].c_str())-1][0], sizeof(vertex2.NORMAL));
								memcpy(vertex3.NORMAL, &normals[atoi(face3[2].c_str())-1][0], sizeof(vertex3.NORMAL));
							}
							_vertexArray.push_back(vertex1);
							_vertexArray.push_back(vertex2);
							_vertexArray.push_back(vertex3);
						}
					}
                }
        }
        else{
			std::cerr << "Cannot open " << fileName << std::endl; exit(1);
		}
}


std::vector<std::string> ObjObject::explode(const std::string &s, char delim){
	int i = 0;
	std::vector<std::string> result;
    std::istringstream iss(s);
    for (std::string token; std::getline(iss, token, delim);)
		result.push_back(token);
	return result;
}

void ObjObject::saveObject(std::string filename){
	std::ofstream outputFile;
	outputFile.open(filename, std::fstream::app);
	outputFile << "   <Object";
	outputFile << " objFileDir = \"";
	outputFile << _objFileDir << "\"";
	outputFile << " color = \"";
	outputFile << _color[0] << ", ";
	outputFile << _color[1] << ", ";
	outputFile << _color[2] << "\"";
	outputFile << " name = \"";
	outputFile << std::string(_name) << "\"";
	outputFile << " texture = \"";
	outputFile << _textureID << "\"";
	outputFile << " selectable = \"";
	outputFile << _selectable << "\">" << std::endl;

	for(int i = 0; i < getPropertiesArraySize(); i++){
		outputFile << "      <Frame";
		outputFile << " position = \"";
		outputFile << _propertiesArray[i].position.x << ", ";
		outputFile << _propertiesArray[i].position.y << ", ";
		outputFile << _propertiesArray[i].position.z << "\"";
		outputFile << " rotation = \"";
		outputFile << _propertiesArray[i].rotation.w << ", ";
		outputFile << _propertiesArray[i].rotation.x << ", ";
		outputFile << _propertiesArray[i].rotation.y << ", ";
		outputFile << _propertiesArray[i].rotation.z << "\"";
		outputFile << " scale = \"";
		outputFile << _propertiesArray[i].scale.x << ", ";
		outputFile << _propertiesArray[i].scale.y << ", ";
		outputFile << _propertiesArray[i].scale.z << "\"";
		outputFile << "/>" << std::endl;
	}

	outputFile << "   </Object>" << std::endl;
	outputFile.close();
}