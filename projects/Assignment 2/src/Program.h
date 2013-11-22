#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <fstream>
#include <iostream>
#include "GL\glew.h"
#include "GL\freeglut.h"

#define VERTEX GL_VERTEX_SHADER
#define FRAGMENT GL_FRAGMENT_SHADER

class Program {

	std::string _vertexFile, _fragmentFile;

	GLuint _programId;
	GLuint _vertexShaderId;
	GLuint _fragmentShaderId;
	GLuint _uniformId;

	char* _vertexShader;
	char* _fragmentShader;

public:
	Program(char* vertexFile, char* fragmentFile) : _vertexFile(vertexFile), _fragmentFile(fragmentFile){}

	void createShaderProgram() {

		_vertexShaderId = loadShaderFromFile(_vertexFile, VERTEX);
		_fragmentShaderId = loadShaderFromFile(_fragmentFile, FRAGMENT);

		_programId = glCreateProgram();
		glAttachShader(_programId, _vertexShaderId);
		glAttachShader(_programId, _fragmentShaderId);
		glBindAttribLocation(_programId, 0, "in_Position");
		glBindAttribLocation(_programId, 1, "in_Color");
		glLinkProgram(_programId);
		_uniformId = glGetUniformLocation(_programId, "Matrix");
	}

	void destroyShaderProgram(){
		glDetachShader(_programId,_vertexShaderId);
		glDetachShader(_programId, _fragmentShaderId);

		glDeleteShader(_vertexShaderId);
		glDeleteShader(_fragmentShaderId);
		glDeleteProgram(_programId);
	}

	GLuint loadShaderFromFile(std::string fileName, GLenum shaderType){
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
				printf( "Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource );
				//printShaderLog( shaderID );
				glDeleteShader( shaderID );
				shaderID = 0;
			}
		}
		else
		{
			printf( "Unable to open file %s\n", fileName);
		}

	 return shaderID;
}

	GLuint getUniformId() { return _uniformId; }
	GLuint getProgramId() { return _programId; }

};

#endif
