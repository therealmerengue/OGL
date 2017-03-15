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
	shaderManager.modelMatrix = glm::rotate(shaderManager.modelMatrix, model.coordinates.rotationAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
	shaderManager.modelMatrix = glm::rotate(shaderManager.modelMatrix, model.coordinates.rotationAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
	shaderManager.modelMatrix = glm::rotate(shaderManager.modelMatrix, model.coordinates.rotationAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
	shaderManager.modelMatrix = glm::translate(shaderManager.modelMatrix, glm::vec3(-0.5f * model.coordinates.size.x, -0.5f * model.coordinates.size.y, -0.5f * model.coordinates.size.z));
	shaderManager.modelMatrix = glm::scale(shaderManager.modelMatrix, model.coordinates.size);
	glUniformMatrix4fv(shaderManager.modelMatLocation, 1, GL_FALSE, glm::value_ptr(shaderManager.modelMatrix));
}

void Renderer::setUpViewMatrix(const Camera& camera)
{
	glm::mat4 viewMatrix;
	shaderManager.viewMatrix = viewMatrix;
	shaderManager.viewMatrix = glm::rotate(shaderManager.viewMatrix, camera.getPitch(), glm::vec3(1.0f, 0.0f, 0.0f));
	shaderManager.viewMatrix = glm::rotate(shaderManager.viewMatrix, camera.getYaw(), glm::vec3(0.0f, 1.0f, 0.0f));
	shaderManager.viewMatrix = glm::rotate(shaderManager.viewMatrix, camera.getRoll(), glm::vec3(0.0f, 0.0f, 1.0f));
	shaderManager.viewMatrix = glm::translate(shaderManager.viewMatrix, -camera.getPosition());
	glUniformMatrix4fv(shaderManager.viewMatLocation, 1, GL_FALSE, glm::value_ptr(shaderManager.viewMatrix));
}

void Renderer::setUpMatrices(const Model& model, const Camera& camera)
{
	setUpModelMatrix(model);
	setUpViewMatrix(camera);
}

Renderer::Renderer(std::string vertexShaderPath, std::string fragmentShaderPath, Camera* camera) : 
	shaderManager(vertexShaderPath, fragmentShaderPath), camera(camera)
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
	setUpMatrices(model, *camera);

	draw(model);
}

void Renderer::renderTexture(const Model& model)
{
	setUpMatrices(model, *camera);

	glActiveTexture(GL_TEXTURE0);
	model.texture.bindTexture();
	
	glUniform3f(glGetUniformLocation(shaderManager.programID, "spriteColor"), model.color.x, model.color.y, model.color.z);

	draw(model);
}
