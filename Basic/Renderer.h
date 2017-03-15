#pragma once
#include "ShaderManager.h"
#include "Model.h"
#include "Texture.h"
#include "Camera.h"

#include <GL\glew.h>

class Renderer
{
private:
	ShaderManager shaderManager;
	Camera* camera;

	void draw(const Model& model);
	void setUpModelMatrix(const Model& model);
	void setUpViewMatrix(const Camera& camera);
	void setUpMatrices(const Model& model, const Camera& camera);

public:
	Renderer(std::string vertexShaderPath, std::string fragmentShaderPath, Camera* camera);
	~Renderer();

	void clearScreen();

	void render(const Model& model);
	void renderTexture(const Model& model);
};

