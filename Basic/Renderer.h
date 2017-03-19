#pragma once
#include "BasicShaderManager.h"
#include "Model.h"
#include "Texture.h"
#include "Camera.h"
#include "Light.h"
#include "Entity.h"

#include <GL\glew.h>

#include <map>

class Renderer
{
private:
	BasicShaderManager shaderManager;
	Camera* camera;

	void draw(const Entity& entity);
	void setUpModelMatrix(const Entity& entity);
	void setUpViewMatrix(const Camera& camera);
	void setUpMatrices(const Entity& entity, const Camera& camera);

public:
	Renderer(const BasicShaderManager& shaderManager, Camera* camera);
	~Renderer();

	void clearScreen();

	void render(const Entity& entity);
	void renderTexture(const Entity& entity);
	
	void render(const std::map<Model*, std::vector<Entity>>& entities);
};

