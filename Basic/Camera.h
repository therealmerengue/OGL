#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>

class Camera
{
private:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	GLfloat pitch = 0.0f, yaw = 0.0f, roll = 0.0f;

public:
	Camera() {}
	~Camera() {}

	GLfloat getPitch() const { return pitch; }
	GLfloat getYaw() const { return yaw; }
	GLfloat getRoll() const { return roll; }
	glm::vec3 getPosition() const { return position; }

	void move();
};

