#include "KeyboardManager.h"

KeyboardManager& KeyboardManager::getInstance()
{
	static KeyboardManager km;
	return km;
}

void KeyboardManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (action == GLFW_PRESS)
		keyStates[key] = GL_TRUE;
	else if (action == GLFW_RELEASE)
		keyStates[key] = GL_FALSE;
}


std::array<GLboolean, 512> KeyboardManager::keyStates = { GL_FALSE };