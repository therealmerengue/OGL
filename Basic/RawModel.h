#pragma once
#include "Coordinates.h"

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

class RawModel
{
public:
	RawModel(GLuint vaoID) : vaoID(vaoID)
	{
	}
	~RawModel();

	std::vector<GLuint> vbosAndEbos;

	GLuint getVaoID() const;
	void rotate(GLfloat angle);
	void move(GLfloat dx, GLfloat dy, GLfloat dz);

	size_t getIndicesSize() const
	{
		return indices.size();
	}

	friend class Renderer;
	friend class ModelBuilder;

private:
	GLuint vaoID;
	Coordinates coordinates;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> vertexColors;
	std::vector<GLuint> indices;
};

