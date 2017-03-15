#pragma once
#include <GLFW\glfw3.h>

#include <array>

class KeyboardManager
{
private:
	KeyboardManager() {}
	static std::array<GLboolean, 512> keyStates;

public:
	~KeyboardManager() {}
	KeyboardManager(KeyboardManager const&) = delete;
	void operator=(KeyboardManager const&) = delete;

	static KeyboardManager& getInstance();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static bool getKeyState(int key) { return keyStates[key]; }
};

