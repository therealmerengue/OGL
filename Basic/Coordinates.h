#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>

struct Coordinates
{
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 rotationAxis;
	GLfloat rotationAngle;

	Coordinates(glm::vec3 position, glm::vec3 size, glm::vec3 rotationAxis, GLfloat rotationAngle);
}; 

