#pragma once
#include "ShaderManager.h"

#include <GL\glew.h>

class Renderer
{
private:
	ShaderManager shaderManager;

	void clearScreen();

public:
	Renderer();
	~Renderer();

	void render(GLuint vaoID);
};

