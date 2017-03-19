#include "EngineTester.h"
#include "InputManager.h"
#include "OBJModelBuilder.h"
#include "BasicShaderManager.h"
#include "LightShaderManager.h"
#include "Light.h"
#include "BasicModelBuilder.h"

#include <iostream>
#include <random>

EngineTester::EngineTester()
{
	initWindow();
	
	BasicModelBuilder sbTex(Dimensions::dim2D, Texture("textures/blue.png"));
	BasicModelBuilder sb(Dimensions::dim2D);

	texEnt = sbTex.Result(glm::vec3(0.0f, 0.0f, -10.0f));
	ent2D = sb.Result(glm::vec3(0.0f, 0.0f, -15.0f));

	OBJModelBuilder omb;

	auto objModel = omb.loadObjModel("models/stall.obj")->Result(Texture("textures/stallTexture.png"));
	objEnt = std::make_unique<Entity>(objModel, glm::vec3(0.0f, 0.0f, -50.0f));

	Texture tex("textures/white.png", 10.0f, 1.0f);
	auto objDragonModel = omb.loadObjModel("models/dragon.obj")->Result(tex);
	objDragonEnt = std::make_unique<Entity>(objDragonModel, glm::vec3(0.0f, 0.0f, -20.0f));

	renderer = std::make_unique<Renderer>(
		BasicShaderManager("shaders/vertexShader.vs", "shaders/fragmentShader.frag"), &camera);
	texRenderer = std::make_unique<Renderer>(
		BasicShaderManager("shaders/texVertexShader.vs", "shaders/texFragmentShader.frag"), &camera);
	Light l(glm::vec3(3000, 2000, 2000), glm::vec3(1.0f, 1.0f, 1.0f));
	lightRenderer = std::make_unique<Renderer>(
		LightShaderManager("shaders/lightVertexShader.vs", "shaders/lightFragmentShader.frag", &l, &tex), &camera);

	masterRenderer = std::make_unique<MasterRenderer>(texRenderer.get());
	BasicModelBuilder bmb3D(Dimensions::dim3D, tex);
	for (size_t i = 0; i < 200; i++)
	{
		auto position = glm::vec3(genRandomNumber(-50, 50), genRandomNumber(-50, 50), genRandomNumber(-100, 0));
		auto cubeEntity = bmb3D.Result(position);
		masterRenderer->addEntity(*cubeEntity.get());
	}
}

EngineTester::~EngineTester()
{
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
	glCullFace(GL_BACK);
}

int EngineTester::genRandomNumber(int begin, int end)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(begin, end); // define the range
	return distr(eng);
}

void EngineTester::printFPS()
{
	float currentFrameTime = glfwGetTime();
	deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
	std::cout << 1 / deltaTime << '\n';
}

void EngineTester::gameLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		printFPS();

		renderer->clearScreen();
		renderer->render(*ent2D);
		lightRenderer->renderTexture(*objDragonEnt);
		renderer->renderTexture(*objEnt);
		texRenderer->renderTexture(*texEnt);
		masterRenderer->render();
		objDragonEnt->rotate(0.0f, 0.002f, 0.0f);
		camera.move();
		glfwSwapBuffers(window);
	}
}