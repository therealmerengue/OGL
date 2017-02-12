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
	RawModel* model2;

	std::array<GLfloat, 12> vertices2D = {
		0.5f,  0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f, 
		-0.5f, -0.5f, 0.0f,  
		-0.5f,  0.5f, 0.0f,
	};
	std::array<GLfloat, 12> vertexColors2D = {
		1.0f, 0.0f, 0.0f,  // Left
		0.0f, 1.0f, 0.0f,  // Right
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};
	std::array<GLuint, 6> indices2D = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	std::array<GLfloat, 72> vertices3D = {
		-0.5f,0.5f,0,
		-0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		0.5f,0.5f,0,

		-0.5f,0.5f,1,
		-0.5f,-0.5f,1,
		0.5f,-0.5f,1,
		0.5f,0.5f,1,

		0.5f,0.5f,0,
		0.5f,-0.5f,0,
		0.5f,-0.5f,1,
		0.5f,0.5f,1,

		-0.5f,0.5f,0,
		-0.5f,-0.5f,0,
		-0.5f,-0.5f,1,
		-0.5f,0.5f,1,

		-0.5f,0.5f,1,
		-0.5f,0.5f,0,
		0.5f,0.5f,0,
		0.5f,0.5f,1,

		-0.5f,-0.5f,1,
		-0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		0.5f,-0.5f,1
	};
	std::array<GLfloat, 72> colors3D = {
		1.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,  
		0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};
	std::array<GLuint, 36> indices3D = {
		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22
	};

	void initWindow();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static std::array<GLboolean, 512> keyStates;
};

