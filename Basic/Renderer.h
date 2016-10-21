#pragma once
#include <GL\glew.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void clearScreen();
	void render(GLuint vaoID, GLuint shaderProgramID);
};

