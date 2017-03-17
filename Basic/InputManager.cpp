#include "InputManager.h"

InputManager& InputManager::getInstance()
{
	static InputManager km;
	return km;
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (action == GLFW_PRESS)
		keyStates[key] = GL_TRUE;
	else if (action == GLFW_RELEASE)
		keyStates[key] = GL_FALSE;
}

void InputManager::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouseMove)
	{
		lastMousePosition.x = xpos;
		lastMousePosition.y = ypos;
		firstMouseMove = false;
	}
	mousePositionOffset.x = xpos - lastMousePosition.x;
	mousePositionOffset.y = ypos - lastMousePosition.y; // Reversed since y-coordinates go from bottom to left
	lastMousePosition.x = xpos;
	lastMousePosition.y = ypos;
}

std::array<GLboolean, 512> InputManager::keyStates = { GL_FALSE };

glm::vec2 InputManager::lastMousePosition(400.0f, 300.0f);
glm::vec2 InputManager::mousePositionOffset(0.0f, 0.0f);
bool InputManager::firstMouseMove = true;