#include "Mesh.h"
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(){
	
	//loadMesh(fileName, vertices);
}

void Mesh::createBufferObject(std::vector<glm::vec4> &vertices){
	glGenVertexArrays(1, VaoId);	//Vertex Array
	glGenBuffers(2, VboId);		//Buffer Array

	glBindVertexArray(VaoId[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec4), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(VERTICES);
	//glDisableVertexAttribArray(COLORS);
}

void Mesh::draw(std::vector<glm::vec4> &vertices, GLuint _selectedProgram){
	glBindVertexArray(VaoId[0]);
	glUseProgram(_selectedProgram);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glUseProgram(0);
	glBindVertexArray(0);
}

void Mesh::loadMesh(const char* fileName, std::vector<glm::vec4> &vertices){
	std::string line = std::string();
	std::ifstream file(fileName);

	std::vector<glm::vec4> temp_vertices;
	//std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<GLushort> temp_elements; //vertexIndices, uvIndices, normalIndices
	
	if (file.is_open()) {
		while (getline(file, line)) {
			if (line.substr(0, 2) == "v ") {    //read vertex; ex: v 1.000000 -1.000000 -1.000000
				std::istringstream s(line.substr(2));
				glm::vec4 v;
				s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
				temp_vertices.push_back(v);
			}
			else if (line.substr(0, 2) == "f ") {   // read faces; ex: f 5 1 4
				std::stringstream s(line.substr(2));
				/*std::string v = s.str();

				std::string a = v.substr(0, 1);
	
				std::string b = v.substr(6, 6).substr(0, 1);
				if (b == " "){
					b = v.substr(7, 7).substr(0, 1);
				}
				std::string c = v.substr(12, 12);
				if (c == " "){
					c = v.substr(13, 13).substr(0, 1);
				}
				else if (v.substr(13, 13).substr(0, 1) == " "){
					c = v.substr(14, 14).substr(0, 1);
				}
				temp_elements.push_back(std::stoi(a));
				temp_elements.push_back(std::stoi(b)); temp_elements.push_back(std::stoi(c));
				*/
				GLushort a, b, c;
				s >> a; s >> b; s >> c;
				a--; b--; c--;

				temp_elements.push_back(a); 
				temp_elements.push_back(b); temp_elements.push_back(c);
			}
			else if (line[0] == '#') {
				/* ignoring this line */
			}
			else {
				/* ignoring this line */
			}
		}

		for (unsigned int i = 0; i < temp_elements.size(); i++){

			// Get the indices of its attributes
			GLushort vertexIndex = temp_elements[i];
			// Get the attributes thanks to the index
			glm::vec4 vertex = temp_vertices[vertexIndex];
			// Put the attributes in buffers
			vertices.push_back(vertex);

		}
		std::cerr << "consegui ler obj" << std::endl;
	}
	else{ std::cerr << "Cannot open " << fileName << std::endl; exit(1); }
}