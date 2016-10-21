#include "Renderer.h"

Renderer::Renderer()
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

void Renderer::render(GLuint vaoID, GLuint shaderProgramID)
{
	glUseProgram(shaderProgramID);
	glBindVertexArray(vaoID);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}
