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
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(GLuint vaoID)
{
	glUseProgram(shaderManager.getProgramID());
	glBindVertexArray(vaoID);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}
