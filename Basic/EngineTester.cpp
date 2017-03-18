#include "EngineTester.h"
#include "InputManager.h"
#include "OBJModelBuilder.h"
#include "BasicShaderManager.h"
#include "LightShaderManager.h"
#include "Light.h"

#include <iostream>

EngineTester::EngineTester()
{
	initWindow();
	model3D = modelBuilder.InitBuild()
		->Coords(Coordinates(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(1.0f, 1.0f, 2.0f), glm::vec3(0.0f, 45.0f, 60.0f)))
		->Vertices(vertices3D)
		->VertexColors(colors3D)
		->Indices(indices3D)
		->Result();
	model2D = modelBuilder.InitBuild()
		->Coords(Coordinates(glm::vec3(1.0f, 1.2f, -5.0f), glm::vec3(1.0f, 1.0f, 2.0f), glm::vec3(0.0f, 30.0f, 45.0f)))
		->Vertices(vertices2D)
		->VertexColors(vertexColors2D)
		->Indices(indices2D)
		->Result();
	texModel = modelBuilder.InitBuild()
		->Coords(Coordinates(glm::vec3(0.5f, 0.5f, -5.0f), glm::vec3(1.0f, 1.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
		->Vertices(vertices2D)
		->TextureCoords(textureCoords)
		->Tex(Texture("textures/blue.png"))
		->Color(glm::vec3(1.0f))
		->Indices(indices2D)
		->Result();

	OBJModelBuilder omb;

	objModel = omb.loadObjModel("models/stall.obj")
		->Result(Coordinates(glm::vec3(0.0f, 0.0f, -50.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)), 
		"textures/stallTexture.png");

	Texture tex("textures/white.png", 10.0f, 1.0f);
	objDragonModel = omb.loadObjModel("models/dragon.obj")
		->Result(Coordinates(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)), tex);
	renderer = new Renderer(BasicShaderManager("shaders/vertexShader.vs", "shaders/fragmentShader.frag"), &camera);
	texRenderer = new Renderer(BasicShaderManager("shaders/texVertexShader.vs", "shaders/texFragmentShader.frag"), &camera);
	Light l(glm::vec3(3000, 2000, 2000), glm::vec3(1.0f, 1.0f, 1.0f));
	lightRenderer = new Renderer(LightShaderManager("shaders/lightVertexShader.vs", "shaders/lightFragmentShader.frag", &l, &tex), &camera);
}

EngineTester::~EngineTester()
{
	delete renderer;
	delete texRenderer;
	delete lightRenderer;
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
	glfwSetKeyCallback(window, InputManager::keyCallback);
	glfwSetCursorPosCallback(window, InputManager::mouseCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
		renderer->renderTexture(*objModel);
		texRenderer->renderTexture(*texModel);
		lightRenderer->renderTexture(*objDragonModel);
		model3D->rotate(RotationAxis::x, 0.002f);
		objDragonModel->rotate(RotationAxis::y, 0.002f);
		camera.move();
		//model->move(0.0f, 0.0f, -0.01f);
		glfwSwapBuffers(window);
	}
}