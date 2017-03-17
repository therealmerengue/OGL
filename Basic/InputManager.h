#pragma once
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include <array>

class InputManager
{
private:
	InputManager() {}
	static std::array<GLboolean, 512> keyStates;
	static glm::vec2 mousePositionOffset;
	static glm::vec2 lastMousePosition;
	static bool firstMouseMove;

public:
	~InputManager() {}
	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;

	static InputManager& getInstance();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static bool getKeyState(int key) { return keyStates[key]; }
	static glm::vec2 getMousePositionOffset() { return mousePositionOffset; }
	static void resetMousePositionOffset() { mousePositionOffset = glm::vec2(0.0f, 0.0f); }
	static glm::vec2 getLastMousePosition() { return lastMousePosition; }
};

