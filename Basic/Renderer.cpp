#include "Renderer.h"
#include "RawModel.h"

Renderer::Renderer() : shaderManager("vertexShader.vs", "fragmentShader.frag")
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

void Renderer::render(const RawModel& model, int numOfElements)
{
	shaderManager.useProgram();
	glm::mat4 modMatrix;
	shaderManager.modelMatrix = modMatrix;
	shaderManager.modelMatrix = glm::translate(shaderManager.modelMatrix, model.coordinates.position);
	shaderManager.modelMatrix = glm::translate(shaderManager.modelMatrix, glm::vec3(0.5f * model.coordinates.size.x, 0.5f * model.coordinates.size.y, 0.5f * model.coordinates.size.z));
	shaderManager.modelMatrix = glm::rotate(shaderManager.modelMatrix, model.coordinates.rotationAngle, model.coordinates.rotationAxis);
	shaderManager.modelMatrix = glm::translate(shaderManager.modelMatrix, glm::vec3(-0.5f * model.coordinates.size.x, -0.5f * model.coordinates.size.y, -0.5f * model.coordinates.size.z));
	shaderManager.modelMatrix = glm::scale(shaderManager.modelMatrix, model.coordinates.size);

	glUniformMatrix4fv(shaderManager.modelMatLocation, 1, GL_FALSE, glm::value_ptr(shaderManager.modelMatrix));
	glBindVertexArray(model.vaoID);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, numOfElements, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
