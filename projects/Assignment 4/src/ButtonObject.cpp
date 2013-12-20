#include "ButtonObject.h"
#include "TextureManager.h"
#include "ButtonTextureProgram.h"
#include <string>

ButtonObject::ButtonObject(std::string name, int textureID, bool selectable, float width, float height, glm::vec2 position) : Object(name){
	_textureID = textureID;
	setColor(0,0,0,1);
	_selectable = selectable;
	Vertex vertex1 = {{position[0],position[1],0,1},{0,0,0,0},{0,1}};					// bottom left
	Vertex vertex2 = {{position[0]+width,position[1]+height, 0, 1}, {0,0,0,0},{1,0}};	// top right
	Vertex vertex3 = {{position[0],position[1]+height, 0, 1}, {0,0,0,0},{0,0}};			//top left
	Vertex vertex4 = {{position[0]+width, position[1], 0, 1}, {0,0,0,0},{1,1}};			//bottom right

	_vertexArray.push_back(vertex1);
	_vertexArray.push_back(vertex2);
	_vertexArray.push_back(vertex3);

	_vertexArray.push_back(vertex2);
	_vertexArray.push_back(vertex1);
	_vertexArray.push_back(vertex4);
}

void ButtonObject::setPrograms(){
	_programsToUse.push_back(_shaderManager->getProgram("NormalButtonShader"));
	_programsToUse.push_back(_shaderManager->getProgram("SelectedButtonShader"));
}

void ButtonObject::saveObject(std::string filename){}

void ButtonObject::createBufferObjects(GLuint* vaoId, GLuint* vboId){
	glBindVertexArray(vaoId[_vaoId]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[_vboId]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_vertexArray.size(), &_vertexArray[0], GL_STATIC_DRAW);
	//Vertex Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//Vertex Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertexArray[0].XYZW));
	//Vertex UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(_vertexArray[0].NORMAL)*2));
}

void ButtonObject::draw(GLuint* vaoId) {
	ButtonTextureProgram* program;
	if(_selected)
		program = ((ButtonTextureProgram*)_programsToUse[1]);
	else
		program = ((ButtonTextureProgram*)_programsToUse[0]);
	program->bind();
	glBindVertexArray(vaoId[_vaoId]);
	glUniform4fv(program->getColorUniformId(), 1, _color);
	if(TextureManager::Inst()->BindTexture(_textureID))
		glUniform1i(program->getTextureUniformId(), 0);
	glDrawArrays(GL_TRIANGLES,0,_vertexArray.size());
	glUseProgram(0);
}

bool ButtonObject::checkIntersection(glm::vec3 rayOrigin, glm::vec3 rayDir, glm::vec3 &outputVec){
	return false;
}


bool ButtonObject::checkIntersection(glm::vec2 mouseClick){
	return mouseClick.x >= _vertexArray[0].XYZW[0] &&  
		   mouseClick.y >= _vertexArray[0].XYZW[1] && 
		   mouseClick.x <= _vertexArray[1].XYZW[0] &&  
		   mouseClick.y <= _vertexArray[1].XYZW[1];
}