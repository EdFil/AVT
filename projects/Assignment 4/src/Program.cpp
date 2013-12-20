#include <fstream>
#include "Program.h"
#include <iostream>
#include <vector>

Program::Program(std::string name, std::string vertexFile, std::string fragmentFile) : _name(name), _vertexFile(vertexFile), _fragmentFile(fragmentFile){
}

void Program::destroyShaderProgram(){
	glDetachShader(_programId,_vertexShaderId);
	glDetachShader(_programId, _fragmentShaderId);

	glDeleteShader(_vertexShaderId);
	glDeleteShader(_fragmentShaderId);
	glDeleteProgram(_programId);
}

void Program::bind() const {
	glUseProgram(_programId);
}

std::string Program::getName(){
	return _name;
}

GLuint Program::loadShaderFromFile(std::string fileName, GLenum shaderType){
	//Open file
	GLuint shaderID = 0;
	std::string shaderString;
	std::ifstream sourceFile( fileName );

	//Source file loaded
	if( sourceFile )
	{
		//Get shader source
		shaderString.assign( ( std::istreambuf_iterator< char >( sourceFile ) ), std::istreambuf_iterator< char >() );

		//Create shader ID
		shaderID = glCreateShader( shaderType );

		//Set shader source
		const GLchar* shaderSource = shaderString.c_str();
		glShaderSource( shaderID, 1, (const GLchar**)&shaderSource, NULL );

		//Compile shader source
		glCompileShader( shaderID );

		//Check shader for errors
		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv( shaderID, GL_COMPILE_STATUS, &shaderCompiled );
		if( shaderCompiled != GL_TRUE )
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
 
	        //The maxLength includes the NULL character
		    std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
			for(int i = 0; i < maxLength; i++)
				std::cout << errorLog[i];
			std::cout << std::endl;
			shaderID = 0;
			glDeleteShader(shaderID);
		}
	}
	else
	{
		std::cout << "Unable to open file %s\n" << fileName << std::endl;
	}

	return shaderID;
}
