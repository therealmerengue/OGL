#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RawModel
{
public:
	RawModel(int vaoID);
	~RawModel();

	int getVaoID() { return vaoID; }

	void rotate(GLfloat angle);

	friend class Renderer;

private:
	int vaoID;
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 rotationAxis;
	GLfloat rotationAngle;
};

