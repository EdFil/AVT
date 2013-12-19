#include "ObjObject.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

ObjObject::ObjObject(std::string fileName) : Object("null"){
	std::vector<std::string> path = explode(fileName, '/');
	_name = explode(path[path.size()-1], '.')[0];
	setColor(0.0f, 0.0f, 0.0f, 1.0f);
	loadMesh(fileName.c_str());
}

ObjObject::ObjObject(std::string name, std::string fileName) : Object(name){
	loadMesh(fileName.c_str());
}

void ObjObject::setPrograms(){
	_programsToUse.push_back(_shaderManager->getProgram("NormalShader"));
	_programsToUse.push_back(_shaderManager->getProgram("SelectedShader"));
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
