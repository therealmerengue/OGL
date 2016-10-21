#pragma once
#include "RawModel.h"

#include <GL\glew.h>
#include <vector>
#include <array>

class ModelFactory
{
public:
	ModelFactory();
	~ModelFactory();

	template<std::size_t VERTICES_SIZE> RawModel* createModel(const std::array<GLfloat, VERTICES_SIZE>& vertices)
	{
		int vaoID = createAndBindVAO();
		storeDataInAttributeList<9, GL_FLOAT>(0, 3, vertices);
		unbindVAO();
		return new RawModel(vaoID);
	}
	template<std::size_t SIZE, GLenum TYPE> void storeDataInAttributeList(int attributeNumber, int coordinateSize, const std::array<GLfloat, SIZE>& data)
	{
		GLuint vboID;
		vbos.push_back(vboID);
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, coordinateSize, TYPE, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(attributeNumber);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

private:
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;

	GLuint createAndBindVAO();
	void unbindVAO();
};

