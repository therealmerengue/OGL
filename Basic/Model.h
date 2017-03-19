#pragma once
#include "Texture.h"

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

class Model
{
public:
	Model(GLuint vaoID) : vaoID(vaoID) {}
	~Model();

	std::vector<GLuint> vbosAndEbos;

	GLuint getVaoID() const;
	bool bindTexture() const;
	
	size_t getIndicesSize() const { return indices.size(); }

	friend class ModelBuilder;
	friend bool operator== (const Model &m1, const Model &m2);

private:
	GLuint vaoID;
	Texture texture;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> vertexColors;
	std::vector<GLfloat> textureCoords;
	std::vector<GLfloat> normals;
	std::vector<GLuint> indices;
};

