#include "ObjObject.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

ObjObject::ObjObject(std::string fileName) : Object("null"){
	std::vector<std::string> path = explode(fileName, '/');
	_name = explode(path[path.size()-1], '.')[0];
	loadMesh(fileName.c_str());
}

ObjObject::ObjObject(std::string name, std::string fileName) : Object(name){
	loadMesh(fileName.c_str());
}

void ObjObject::loadMesh(const char* fileName){
        std::string line = std::string();
        std::ifstream file(fileName);

        std::vector<glm::vec4> temp_vertices;
        //std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<int> temp_elements; //vertexIndices, uvIndices, normalIndices
        
        if (file.is_open()) {
                while (getline(file, line)) {
					std::vector<std::string> splitedLine = explode(line, ' ');
					if(splitedLine[0] == "v"){
						float x = atof(&splitedLine[1][0]);
						float y = atof(&splitedLine[2][0]);
						float z = atof(&splitedLine[3][0]);
						temp_vertices.push_back(glm::vec4(x,y,z,1.0f));
					}
					else if(splitedLine[0] == "f"){
						int index1 = atoi(&explode(splitedLine[1], '/')[0][0]);
						int index2 = atoi(&explode(splitedLine[2], '/')[0][0]);
						int index3 = atoi(&explode(splitedLine[3], '/')[0][0]);
						temp_elements.push_back(index1);
						temp_elements.push_back(index2);
						temp_elements.push_back(index3);
					}
                }

                for (unsigned int i = 0; i < temp_elements.size(); i++){
                        glm::vec4 vertex = temp_vertices[temp_elements[i]-1];
						Vertex finalVertex = {{vertex.x,vertex.y,vertex.z,vertex.w},{0.5f,0.5f,0.5f,1.0f}};
						_vertexArray.push_back(finalVertex);
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