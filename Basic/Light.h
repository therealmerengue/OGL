#pragma once
#include <glm\glm.hpp>

class Light
{
private:
	glm::vec3 color, position;

public:
	Light(glm::vec3 position, glm::vec3 color);
	~Light() {}

	glm::vec3 getColor() const { return color; }
	glm::vec3 getPosition() const { return position; }
};

