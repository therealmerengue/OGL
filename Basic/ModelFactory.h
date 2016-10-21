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

	template<typename T, std::size_t VERTICES_SIZE> RawModel* createModel(const std::array<T, VERTICES_SIZE>& vertices)
	{
		int vaoID = createAndBindVAO();
		storeDataInAttributeList<GLfloat, 9>(0, 3, GL_FLOAT, 3, 0, vertices);
		unbindVAO();
		return new RawModel(vaoID);
	}
	template<typename T, std::size_t SIZE> 
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, GLenum type, int stride, int offset, const std::array<T, SIZE>& data)
	{
		GLuint vboID;
		vbos.push_back(vboID);
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, coordinateSize, type, GL_FALSE, stride * sizeof(T), (GLvoid*)(offset * sizeof(T)));
		glEnableVertexAttribArray(attributeNumber);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

private:
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;

	GLuint createAndBindVAO();
	void unbindVAO();
};

