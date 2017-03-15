#include "Camera.h"
#include "KeyboardManager.h"

#include <GLFW\glfw3.h>

void Camera::move()
{
	auto& keyboardManager = KeyboardManager::getInstance();
	if (keyboardManager.getKeyState(GLFW_KEY_W) || keyboardManager.getKeyState(GLFW_KEY_UP))
		position.z -= 0.01f;
	if (keyboardManager.getKeyState(GLFW_KEY_D) || keyboardManager.getKeyState(GLFW_KEY_RIGHT))
		position.x += 0.01f;
	if (keyboardManager.getKeyState(GLFW_KEY_A) || keyboardManager.getKeyState(GLFW_KEY_LEFT))
		position.x -= 0.01f;
	if (keyboardManager.getKeyState(GLFW_KEY_S) || keyboardManager.getKeyState(GLFW_KEY_DOWN))
		position.z += 0.01f;
}
