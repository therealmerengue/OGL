#include "EngineTester.h"

#include <iostream>

EngineTester::EngineTester()
{
	initWindow();
	model = modelFactory.createModel<GLfloat, 72, 36>(vertices3D, colors3D, indices3D);
	renderer = new Renderer();
}

EngineTester::~EngineTester()
{
	delete model;
	delete renderer;
	glfwTerminate();
}

void EngineTester::initWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create GLFW window.\n";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW.\n";
		glfwTerminate();
		return;
	}

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
}

void EngineTester::gameLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		renderer->render(*model);
		model->rotate(0.02f);
		model->move(0.0f, 0.0f, -0.01f);
		glfwSwapBuffers(window);
	}
}

void EngineTester::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (action == GLFW_PRESS)
		keyStates[key] = GL_TRUE;
	else if (action == GLFW_RELEASE)
		keyStates[key] = GL_FALSE;
}

std::array<GLboolean, 512> EngineTester::keyStates = { GL_FALSE };
