#pragma once
#include "BasicShaderManager.h"
#include "Light.h"
#include "Texture.h"

class LightShaderManager : public BasicShaderManager
{
private:
	Light* light;
	Texture* texture;
public:
	LightShaderManager(std::string vertexShaderPath, std::string fragmentShaderPath, Light* light, Texture* texture);
	virtual ~LightShaderManager() {}
};

