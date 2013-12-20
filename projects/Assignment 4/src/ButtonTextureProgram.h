#ifndef BUTTON_TEXTURE_PROGRAM_H
#define BUTTON_TEXTURE_PROGRAM_H

#include "Program.h"

class ButtonTextureProgram : public Program {

protected:
	GLuint _colorUniformId;
	GLuint _textureUniformId;

public:
	ButtonTextureProgram(std::string name, std::string vertexFile, std::string fragmentFile);

	void createShaderProgram();

	GLuint getColorUniformId() const  { return _colorUniformId; }
	GLuint getTextureUniformId() const  { return _textureUniformId; }

};

#endif
