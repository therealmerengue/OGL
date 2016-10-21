#include "Renderer.h"

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

void Renderer::render(GLuint vaoID)
{
	clearScreen();
	shaderManager.useProgram();
	//shaderManager.model = glm::translate(shaderManager.model, glm::vec3(0.0f, 0.0f, -0.5f));
	shaderManager.model = glm::rotate(shaderManager.model, 0.5f, glm::vec3(1.0f, 0.3f, 0.5f));
	glUniformMatrix4fv(shaderManager.modelLocation, 1, GL_FALSE, glm::value_ptr(shaderManager.model));
	glBindVertexArray(vaoID);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
