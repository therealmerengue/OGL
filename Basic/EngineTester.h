#pragma once
#include "BasicShaderManager.h"
#include "Renderer.h"
#include "ModelBuilder.h"
#include "Model.h"
#include "Camera.h"
#include "MasterRenderer.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <array>
#include <vector>
#include <memory>

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

	float deltaTime;
	float lastFrameTime;

	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Renderer> texRenderer;
	std::unique_ptr<Renderer> lightRenderer;
	std::unique_ptr<MasterRenderer> masterRenderer;

	ModelBuilder modelBuilder;
	std::shared_ptr<Entity> ent2D;
	std::shared_ptr<Entity> texEnt;
	std::unique_ptr<Entity> objEnt;
	std::unique_ptr<Entity> objDragonEnt;

	Camera camera;

	void initWindow();
	int genRandomNumber(int begin, int end);
	void printFPS();
};

