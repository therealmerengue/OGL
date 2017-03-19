#include "Texture.h"

#include <soil/SOIL.h>

Texture::Texture(const GLchar* texturePath, GLfloat shineDumper, GLfloat reflectivity) :
	reflectivity(reflectivity), shineDumper(shineDumper)
{
	glGenTextures(1, &ID);

	int width, height;

	unsigned char* textureImage = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGBA); //loading an image

	generateTexture(width, height, textureImage); //generating a texture

	SOIL_free_image_data(textureImage);
}

void Texture::generateTexture(GLuint width, GLuint height, unsigned char* data)
{
	this->width = width;
	this->height = height;

	//creating a texture
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
	
	//setting texture wrapping and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::bindTexture() const //to bind a texture in drawSprite in Renderer
{
	if (width != 0 && height != 0)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
		return true;
	}
	return false;
}