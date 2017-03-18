#pragma once
#include "BasicShaderManager.h"
#include "Model.h"
#include "Texture.h"
#include "Camera.h"
#include "Light.h"

#include <GL\glew.h>

class Renderer
{
private:
	BasicShaderManager shaderManager;
	Camera* camera;

	void draw(const Model& model);
	void setUpModelMatrix(const Model& model);
	void setUpViewMatrix(const Camera& camera);
	void setUpMatrices(const Model& model, const Camera& camera);

public:
	Renderer(const BasicShaderManager& shaderManager, Camera* camera);
	~Renderer();

	void clearScreen();

	void render(const Model& model);
	void renderTexture(const Model& model);
};

