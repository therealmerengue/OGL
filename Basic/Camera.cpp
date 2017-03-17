#include "Camera.h"
#include "InputManager.h"

#include <GLFW\glfw3.h>

void Camera::move()
{
	auto& inputManager = InputManager::getInstance();
	if (inputManager.getKeyState(GLFW_KEY_W) || inputManager.getKeyState(GLFW_KEY_UP))
		position.z -= 0.01f;
	if (inputManager.getKeyState(GLFW_KEY_D) || inputManager.getKeyState(GLFW_KEY_RIGHT))
		position.x += 0.01f;
	if (inputManager.getKeyState(GLFW_KEY_A) || inputManager.getKeyState(GLFW_KEY_LEFT))
		position.x -= 0.01f;
	if (inputManager.getKeyState(GLFW_KEY_S) || inputManager.getKeyState(GLFW_KEY_DOWN))
		position.z += 0.01f;

	GLfloat xoffset = InputManager::getMousePositionOffset().x * sensitivity;
	GLfloat yoffset = InputManager::getMousePositionOffset().y * sensitivity;

	InputManager::resetMousePositionOffset();

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}
