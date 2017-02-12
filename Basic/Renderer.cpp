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
