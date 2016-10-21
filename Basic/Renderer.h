#pragma once
#include "ShaderManager.h"

#include <GL\glew.h>

class Renderer
{
private:
	ShaderManager shaderManager;

public:
	Renderer();
	~Renderer();

	void clearScreen();
	void render(GLuint vaoID);
};

