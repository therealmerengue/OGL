#pragma once
#include "ShaderManager.h"

#include <GL\glew.h>

class Renderer
{
private:
	ShaderManager shaderManager;

	void clearScreen();
	void useShaderProgram();

public:
	Renderer();
	~Renderer();

	void render(GLuint vaoID);
};

