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

	auto model3D = modelBuilder.InitBuild()
		->Vertices(vertices3D)
		->VertexColors(colors3D)
		->Indices(indices3D)
		->Result();
	ent3D = std::make_unique<Entity>(model3D, glm::vec3(0.0f, 0.0f, -5.0f));

	auto model2D = modelBuilder.InitBuild()
		->Vertices(vertices2D)
		->VertexColors(vertexColors2D)
		->Indices(indices2D)
		->Result();
	ent2D = std::make_unique<Entity>(model2D, glm::vec3(1.0f, 1.2f, -5.0f));
	
	auto texModel = modelBuilder.InitBuild()
		->Vertices(vertices2D)
		->TextureCoords(textureCoords)
		->Tex(Texture("textures/blue.png"))
		->Indices(indices2D)
		->Result();
	texEnt = std::make_unique<Entity>(texModel, glm::vec3(0.5f, 0.5f, -5.0f));

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

void EngineTester::gameLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		renderer->clearScreen();
		renderer->render(*ent3D);
		renderer->render(*ent2D);
		lightRenderer->renderTexture(*objDragonEnt);
		renderer->renderTexture(*objEnt);
		texRenderer->renderTexture(*texEnt);
		ent3D->rotate(0.0f, 0.002f, 0.0f);
		objDragonEnt->rotate(0.0f, 0.002f, 0.0f);
		camera.move();
		glfwSwapBuffers(window);
	}
}