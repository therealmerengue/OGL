#pragma once
#include "Coordinates.h"
#include "Texture.h"

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

enum class RotationAxis 
{
	x, y, z
};

class Model
{
public:
	Model(GLuint vaoID) : vaoID(vaoID) {}
	~Model();

	std::vector<GLuint> vbosAndEbos;

	GLuint getVaoID() const;
	void rotate(RotationAxis axis, GLfloat angle);
	void rotate(GLfloat rx, GLfloat ry, GLfloat rz);
	void move(GLfloat dx, GLfloat dy, GLfloat dz);

	size_t getIndicesSize() const { return indices.size(); }

	friend class Renderer;
	friend class ModelBuilder;

private:
	GLuint vaoID;
	Coordinates coordinates;
	Texture texture;
	glm::vec3 color;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> vertexColors;
	std::vector<GLfloat> textureCoords;
	std::vector<GLuint> indices;
};

