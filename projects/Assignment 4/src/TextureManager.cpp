#include "TextureManager.h"
#include "SOIL.h"

const GLuint TextureManager::WOOD_TEXTURE = 0;
const GLuint TextureManager::RED = 1;
const GLuint TextureManager::GREEN = 2;
const GLuint TextureManager::BLUE = 3;
const GLuint TextureManager::WHITE = 4;
const GLuint TextureManager::BROWN = 5;
const GLuint TextureManager::GRAY = 6;
const GLuint TextureManager::YELLOW = 7;
const GLuint TextureManager::PLAY = 8;
const GLuint TextureManager::EDIT = 9;
const GLuint TextureManager::SCREENSHOT = 10;
const GLuint TextureManager::SAVE = 11;
const GLuint TextureManager::LOAD = 12;


TextureManager* TextureManager::_inst(0);

TextureManager* TextureManager::Inst()
{
	if(!_inst)
		_inst = new TextureManager();

	return _inst;
}

TextureManager::TextureManager(){
	_texID = std::vector<GLuint>(13);
	glGenTextures(13, &_texID[0]); 
	loadTexture("../src/objs/wood.jpg", WOOD_TEXTURE);
	loadTexture("../src/objs/red.png", RED);
	loadTexture("../src/objs/green.png", GREEN); 
	loadTexture("../src/objs/blue.png", BLUE);
	loadTexture("../src/objs/white.png", WHITE);
	loadTexture("../src/objs/brown.png", BROWN);
	loadTexture("../src/objs/gray.png", GRAY);
	loadTexture("../src/objs/yellow.png", YELLOW);
	loadTexture("../src/objs/Play.png", PLAY);
	loadTexture("../src/objs/Edit.png", EDIT);
	loadTexture("../src/objs/Screenshot.png", SCREENSHOT);
	loadTexture("../src/objs/Save.png", SAVE);
	loadTexture("../src/objs/Load.png", LOAD);
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