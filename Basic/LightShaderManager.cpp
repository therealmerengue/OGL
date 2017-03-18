#include "LightShaderManager.h"

LightShaderManager::LightShaderManager(std::string vertexShaderPath, std::string fragmentShaderPath, Light* light, Texture* texture) :
	BasicShaderManager(vertexShaderPath, fragmentShaderPath), light(light), texture(texture)
{
	useProgram();

	GLuint id = getProgramID();
	uniformLocations["lightPosition"] = glGetUniformLocation(id, "lightPosition");
	uniformLocations["lightColor"] = glGetUniformLocation(id, "lightColor");
	uniformLocations["shineDamper"] = glGetUniformLocation(id, "shineDamper");
	uniformLocations["reflectivity"] = glGetUniformLocation(id, "reflectivity");

	auto lightPosition = light->getPosition();
	auto lightColor = light->getColor();

	glUniform3f(uniformLocations["lightPosition"], lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(uniformLocations["lightColor"], lightColor.x, lightColor.y, lightColor.z);

	glUniform1f(uniformLocations["shineDamper"], texture->getShineDumper());
	glUniform1f(uniformLocations["reflectivity"], texture->getReflectivity());
}
