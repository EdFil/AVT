#include "TextureManager.h"
#include "SOIL.h"

const GLuint TextureManager::WOOD_TEXTURE = 0;

TextureManager* TextureManager::_inst(0);

TextureManager* TextureManager::Inst()
{
	if(!_inst)
		_inst = new TextureManager();

	return _inst;
}

TextureManager::TextureManager(){
	std::cout << isOpenGLError();
	_texID = std::vector<GLuint>(1);
	int width, height;
	unsigned char* image = SOIL_load_image("../src/objs/wood2.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &_texID[0]); 
	glBindTexture(GL_TEXTURE_2D, _texID[WOOD_TEXTURE]);
	glTexImage2D(GL_TEXTURE_2D, WOOD_TEXTURE, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering (optional)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering (optional)
	SOIL_free_image_data(image);
}

//these should never be called
//TextureManager::TextureManager(const TextureManager& tm){}
//TextureManager& TextureManager::operator=(const TextureManager& tm){}
	
TextureManager::~TextureManager(){
	UnloadAllTextures();
	_inst = 0;
}

bool TextureManager::LoadTexture(const char* filename, const unsigned int texID, GLenum image_format, GLint internal_format, GLint level, GLint border) {
	//Not implemented
	return false;
}

bool TextureManager::UnloadTexture(const unsigned int texID){
	bool result(true);
	//if this texture ID mapped, unload it's texture, and remove it from the vector
	if(texID < _texID.size()){
		glDeleteTextures(1, &(_texID[texID]));
		_texID.erase(_texID.begin()+texID);
	}
	//otherwise, unload failed
	else
	{
		result = false;
	}

	return result;
}

bool TextureManager::BindTexture(const unsigned int texID)
{
	bool result(true);
	//if this texture ID mapped, bind it's texture as current
	if(texID < _texID.size())
		glBindTexture(GL_TEXTURE_2D, _texID[texID]);
	//otherwise, binding failed
	else
		result = false;

	return result;
}

void TextureManager::UnloadAllTextures(){
	while(!_texID.empty())
		UnloadTexture(0);
}