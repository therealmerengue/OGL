#include "Renderer.h"
#include "Model.h"

void Renderer::draw(const Model& model)
{
	glBindVertexArray(model.vaoID);
	glDrawElements(GL_TRIANGLES, model.getIndicesSize(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::setUpModelMatrix(const Model& model)
{
	shaderManager.useProgram();
	glm::mat4 modMatrix;
	shaderManager.modelMatrix = modMatrix;
	shaderManager.modelMatrix = glm::translate(shaderManager.modelMatrix, model.coordinates.position);
	shaderManager.modelMatrix = glm::translate(shaderManager.modelMatrix, glm::vec3(0.5f * model.coordinates.size.x, 0.5f * model.coordinates.size.y, 0.5f * model.coordinates.size.z));
	shaderManager.modelMatrix = glm::rotate(shaderManager.modelMatrix, model.coordinates.rotationAngle, model.coordinates.rotationAxis);
	shaderManager.modelMatrix = glm::translate(shaderManager.modelMatrix, glm::vec3(-0.5f * model.coordinates.size.x, -0.5f * model.coordinates.size.y, -0.5f * model.coordinates.size.z));
	shaderManager.modelMatrix = glm::scale(shaderManager.modelMatrix, model.coordinates.size);
}

Renderer::Renderer(std::string vertexShaderPath, std::string fragmentShaderPath) : shaderManager(vertexShaderPath, fragmentShaderPath)
{
}

Renderer::~Renderer()
{
}

void Renderer::clearScreen()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const Model& model)
{
	setUpModelMatrix(model);

	glUniformMatrix4fv(shaderManager.modelMatLocation, 1, GL_FALSE, glm::value_ptr(shaderManager.modelMatrix));

	draw(model);
}

void Renderer::renderTexture(const Model& model)
{
	setUpModelMatrix(model);

	glActiveTexture(GL_TEXTURE0);
	model.texture.bindTexture();

	glUniformMatrix4fv(shaderManager.modelMatLocation, 1, GL_FALSE, glm::value_ptr(shaderManager.modelMatrix));
	glUniform3f(glGetUniformLocation(shaderManager.programID, "spriteColor"), model.color.x, model.color.y, model.color.z);

	draw(model);
}
