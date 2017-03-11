#pragma once
#include "ShaderManager.h"
#include "Model.h"
#include "Texture.h"

#include <GL\glew.h>

class Renderer
{
private:
	ShaderManager shaderManager;

	void draw(const Model& model);
	void setUpModelMatrix(const Model& model);

public:
	Renderer(std::string vertexShaderPath, std::string fragmentShaderPath);
	~Renderer();

	void clearScreen();

	void render(const Model& model);
	void renderTexture(const Model& model);
};

