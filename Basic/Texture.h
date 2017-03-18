#pragma once

#include <GL\glew.h>

class Texture
{
private:
	GLuint ID;
	GLuint width, height;
	GLuint imageFormat = GL_RGBA;
	GLuint internalFormat = GL_RGBA;
	GLuint wrapS = GL_REPEAT, wrapT = GL_REPEAT;
	GLuint filterMin = GL_LINEAR, filterMax = GL_LINEAR;

	GLfloat shineDumper = 1;
	GLfloat reflectivity = 0;

	void generateTexture(GLuint width, GLuint height, unsigned char* data);

public:
	Texture(const GLchar* texturePath, GLfloat shineDumper = 1, GLfloat reflectivity = 0);
	Texture() {}
	~Texture() {}

	void bindTexture() const;

	GLuint getID() { return this->ID; }

	GLfloat getShineDumper() const { return shineDumper; }
	GLfloat getReflectivity() const { return reflectivity; }
};

