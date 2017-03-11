#include "EngineTester.h"

#include <iostream>

EngineTester::EngineTester()
{
	initWindow();
	model3D = modelBuilder.InitBuild()
		->Coords(Coordinates(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(1.0f, 1.0f, 2.0f), glm::vec3(0.0f, 1.0f, -1.0f), 20.0f))
		->Vertices(vertices3D)
		->VertexColors(colors3D)
		->Indices(indices3D)
		->Result();
	model2D = modelBuilder.InitBuild()
		->Coords(Coordinates(glm::vec3(1.0f, 1.2f, -5.0f), glm::vec3(1.0f, 1.0f, 2.0f), glm::vec3(0.0f, 1.0f, -1.0f), 20.0f))
		->Vertices(vertices2D)
		->VertexColors(vertexColors2D)
		->Indices(indices2D)
		->Result();
	texModel = modelBuilder.InitBuild()
		->Coords(Coordinates(glm::vec3(0.5f, 0.5f, -5.0f), glm::vec3(1.0f, 1.0f, 2.0f), glm::vec3(0.0f, 1.0f, -1.0f), 0.0f))
		->Vertices(vertices2D)
		->TextureCoords(textureCoords)
		->Tex(Texture("textures/blue.png"))
		->Color(glm::vec3(1.0f))
		->Indices(indices2D)
		->Result();
	renderer = new Renderer("vertexShader.vs", "fragmentShader.frag");
	texRenderer = new Renderer("texVertexShader.vs", "texFragmentShader.frag");
}

EngineTester::~EngineTester()
{
	delete renderer;
	delete texRenderer;
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
}

void EngineTester::gameLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		renderer->clearScreen();
		renderer->render(*model3D);
		renderer->render(*model2D);
		texRenderer->renderTexture(*texModel);
		model3D->rotate(0.002f);
		//model->move(0.0f, 0.0f, -0.01f);
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
