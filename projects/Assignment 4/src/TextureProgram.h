#ifndef TEXTURE_PROGRAM_H
#define TEXTURE_PROGRAM_H

#include "Program.h"

class TextureProgram : public Program {

protected:
	GLuint _modelMatrixUniformId;
	GLuint _colorUniformId;
	GLuint _sharedMatrixUboId;
	GLuint _textureUniformId;

public:
	TextureProgram(std::string name, std::string vertexFile, std::string fragmentFile);

	void createShaderProgram();

	GLuint getColorUniformId() const  { return _colorUniformId; }
	GLuint getModelMatrixUniformId() const  { return _modelMatrixUniformId; }
	GLuint getSharedMatrixUboId() const { return _sharedMatrixUboId; }
	GLuint getTextureUniformId() const  { return _textureUniformId; }

};

#endif
