#pragma once
#include "RawModel.h"
#include "Coordinates.h"

#include <GL\glew.h>
#include <vector>
#include <array>

class ModelFactory
{
public:
	ModelFactory();
	~ModelFactory();

	template<std::size_t COORDINATES_SIZE, std::size_t INDICES_SIZE>
	RawModel<COORDINATES_SIZE, INDICES_SIZE>* createModel(const std::array<GLfloat, COORDINATES_SIZE>& vertices,
		const std::array<GLfloat, COORDINATES_SIZE>& vertexColors, 
		const std::array<GLuint, INDICES_SIZE>& indices, 
		Coordinates coordinates)
	{
		int vaoID = createAndBindVAO();
		storeDataInAttributeList<COORDINATES_SIZE>(GL_ARRAY_BUFFER, 0, 3, GL_FLOAT, 3, 0, vertices);
		storeDataInAttributeList<COORDINATES_SIZE>(GL_ARRAY_BUFFER, 1, 3, GL_FLOAT, 3, 0, vertexColors);
		storeVertexIndices<INDICES_SIZE>(indices);
		unbindVAO();
		return new RawModel<COORDINATES_SIZE, INDICES_SIZE>(vaoID, coordinates, vertices, vertexColors, indices);
	}

	template<std::size_t SIZE> 
	void storeDataInAttributeList(GLenum bufferType, int attributeNumber, int coordinateSize, GLenum type, int stride, int offset, 
		const std::array<GLfloat, SIZE>& data)
	{
		GLuint vboID;
		vbosAndEbos.push_back(vboID);
		glGenBuffers(1, &vboID);
		glBindBuffer(bufferType, vboID);
		glBufferData(bufferType, sizeof(data), data.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, coordinateSize, type, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
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

