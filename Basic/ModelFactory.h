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
		storeDataInAttributeList<GLfloat, 9>(GL_ARRAY_BUFFER, 0, 3, GL_FLOAT, 3, 0, vertices);
		unbindVAO();
		return new RawModel(vaoID);
	}

	template<typename T, std::size_t VERTICES_SIZE, std::size_t INDICES_SIZE>
	RawModel* createModel(const std::array<T, VERTICES_SIZE>& vertices, const std::array<T, VERTICES_SIZE>& vertexColors, const std::array<GLuint, INDICES_SIZE>& indices)
	{
		int vaoID = createAndBindVAO();
		storeDataInAttributeList<GLfloat, 12>(GL_ARRAY_BUFFER, 0, 3, GL_FLOAT, 3, 0, vertices);
		storeDataInAttributeList<GLfloat, 12>(GL_ARRAY_BUFFER, 1, 3, GL_FLOAT, 3, 0, vertexColors);
		storeVertexIndices<6>(indices);
		unbindVAO();
		return new RawModel(vaoID);
	}

	template<typename T, std::size_t SIZE> 
	void storeDataInAttributeList(GLenum bufferType, int attributeNumber, int coordinateSize, GLenum type, int stride, int offset, const std::array<T, SIZE>& data)
	{
		GLuint vboID;
		vbosAndEbos.push_back(vboID);
		glGenBuffers(1, &vboID);
		glBindBuffer(bufferType, vboID);
		glBufferData(bufferType, sizeof(data), data.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, coordinateSize, type, GL_FALSE, stride * sizeof(T), (GLvoid*)(offset * sizeof(T)));
		glEnableVertexAttribArray(attributeNumber);
		glBindBuffer(bufferType, 0);
	}

	template<std::size_t SIZE>
	void storeVertexIndices(const std::array<GLuint, SIZE>& indices)
	{
		GLuint eboID;
		vbosAndEbos.push_back(eboID);
		glGenBuffers(1, &eboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
	}

private:
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbosAndEbos;

	GLuint createAndBindVAO();
	void unbindVAO();
};

