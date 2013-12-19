#include "TextureManager.h"
#include "SOIL.h"

const GLuint TextureManager::WOOD_TEXTURE = 0;
const GLuint TextureManager::RED = 1;
const GLuint TextureManager::GREEN = 2;
const GLuint TextureManager::BLUE = 3;

TextureManager* TextureManager::_inst(0);

TextureManager* TextureManager::Inst()
{
	if(!_inst)
		_inst = new TextureManager();

	return _inst;
}

TextureManager::TextureManager(){
	_texID = std::vector<GLuint>(4);
	glGenTextures(4, &_texID[0]); 
	loadTexture("../src/objs/wood2.jpg", WOOD_TEXTURE);
	loadTexture("../src/objs/red.png", RED);
	loadTexture("../src/objs/green.png", GREEN); 
	loadTexture("../src/objs/blue.png", BLUE);
}

void TextureManager::loadTexture(const char* dirName, int textID){
	int width, height;
	unsigned char* image = SOIL_load_image(dirName, &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, _texID[textID]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image);
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