#include "LightShaderManager.h"

LightShaderManager::LightShaderManager(std::string vertexShaderPath, std::string fragmentShaderPath, Light* light) :
	BasicShaderManager(vertexShaderPath, fragmentShaderPath), light(light)
{
	useProgram();
	GLuint id = getProgramID();
	uniformLocations["lightPosition"] = glGetUniformLocation(id, "lightPosition");
	uniformLocations["lightColor"] = glGetUniformLocation(id, "lightColor");

	auto lightPosition = light->getPosition();
	auto lightColor = light->getColor();

	glUniform3f(uniformLocations["lightPosition"], lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(uniformLocations["lightColor"], lightColor.x, lightColor.y, lightColor.z);
}
