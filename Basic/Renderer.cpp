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
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, model.coordinates.position);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f * model.coordinates.size.x, 0.5f * model.coordinates.size.y, 0.5f * model.coordinates.size.z));
	modelMatrix = glm::rotate(modelMatrix, model.coordinates.rotationAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, model.coordinates.rotationAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, model.coordinates.rotationAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f * model.coordinates.size.x, -0.5f * model.coordinates.size.y, -0.5f * model.coordinates.size.z));
	modelMatrix = glm::scale(modelMatrix, model.coordinates.size);
	glUniformMatrix4fv(shaderManager.getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Renderer::setUpViewMatrix(const Camera& camera)
{
	glm::mat4 viewMatrix;
	viewMatrix = glm::rotate(viewMatrix, camera.getPitch(), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, camera.getYaw(), glm::vec3(0.0f, 1.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, camera.getRoll(), glm::vec3(0.0f, 0.0f, 1.0f));
	viewMatrix = glm::translate(viewMatrix, -camera.getPosition());
	glUniformMatrix4fv(shaderManager.getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void Renderer::setUpMatrices(const Model& model, const Camera& camera)
{
	setUpModelMatrix(model);
	setUpViewMatrix(camera);
}

Renderer::Renderer(const BasicShaderManager& shaderManager, Camera* camera) :
	shaderManager(shaderManager), camera(camera)
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
	
	glUniform3f(glGetUniformLocation(shaderManager.getProgramID(), "spriteColor"), model.color.x, model.color.y, model.color.z);

	draw(model);
}
