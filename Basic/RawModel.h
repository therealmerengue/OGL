#pragma once
#include "Coordinates.h"

#include <GL\glew.h>
#include <glm\glm.hpp>

class RawModel
{
public:
	RawModel(int vaoID, Coordinates coordinates);
	~RawModel();

	int getVaoID() { return vaoID; }

	void rotate(GLfloat angle) { coordinates.rotationAngle += angle; }
	void move(GLfloat dx, GLfloat dy, GLfloat dz) { coordinates.position += glm::vec3(dx, dy, dz); }

	friend class Renderer;

private:
	int vaoID;
	Coordinates coordinates;
};

