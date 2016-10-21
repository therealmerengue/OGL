#pragma once
#include "ShaderManager.h"
#include "Renderer.h"
#include "ModelFactory.h"
#include "RawModel.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class EngineTester
{
public:
	EngineTester();
	~EngineTester();

	void gameLoop();

private:
	int width = 800;
	int height = 600;
	const char* title = "GAME";
	GLFWwindow* window;
	Renderer* renderer;
	ModelFactory modelFactory;
	RawModel* model;

	std::array<GLfloat, 12> vertices = {
		0.5f,  0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f, 
		-0.5f, -0.5f, 0.0f,  
		-0.5f,  0.5f, 0.0f,
	};
	std::array<GLfloat, 12> vertexColors = {
		1.0f, 0.0f, 0.0f,  // Left
		0.0f, 1.0f, 0.0f,  // Right
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};
	std::array<GLuint, 6> indices = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	void initWindow();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

