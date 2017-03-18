#pragma once
#include "BasicShaderManager.h"
#include "Light.h"

class LightShaderManager : public BasicShaderManager
{
private:
	Light* light;
public:
	LightShaderManager(std::string vertexShaderPath, std::string fragmentShaderPath, Light* light);
	virtual ~LightShaderManager() {}
};

