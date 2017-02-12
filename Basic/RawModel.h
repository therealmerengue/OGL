#pragma once
#include "Coordinates.h"

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <array>

template<size_t COORDINATES_SIZE, size_t INDICES_SIZE>
class RawModel
{
public:
	RawModel(int vaoID, const Coordinates& coordinates, const std::array<GLfloat, COORDINATES_SIZE>& vertices,
		const std::array<GLfloat, COORDINATES_SIZE>& colors, const std::array<GLuint, INDICES_SIZE>& indices);

	int getVaoID();
	void rotate(GLfloat angle);
	void move(GLfloat dx, GLfloat dy, GLfloat dz);

	friend class Renderer;

private:
	int vaoID;
	Coordinates coordinates;

	std::array<GLfloat, COORDINATES_SIZE> vertices;
	std::array<GLfloat, COORDINATES_SIZE> vertexColors;
	std::array<GLuint, INDICES_SIZE> indices;
};

template<size_t COORDINATES_SIZE, size_t INDICES_SIZE>
RawModel<COORDINATES_SIZE, INDICES_SIZE>::RawModel(int vaoID, const Coordinates& coordinates, const std::array<GLfloat, COORDINATES_SIZE>& vertices,
	const std::array<GLfloat, COORDINATES_SIZE>& colors, const std::array<GLuint, INDICES_SIZE>& indices) :
	vaoID(vaoID), coordinates(coordinates), vertices(vertices), vertexColors(colors), indices(indices)
{
}

template<size_t COORDINATES_SIZE, size_t INDICES_SIZE> 
int RawModel<COORDINATES_SIZE, INDICES_SIZE>::getVaoID() 
{ 
	return vaoID; 
}

template<size_t COORDINATES_SIZE, size_t INDICES_SIZE> 
void RawModel<COORDINATES_SIZE, INDICES_SIZE>::rotate(GLfloat angle) 
{ 
	coordinates.rotationAngle += angle; 
}

template<size_t COORDINATES_SIZE, size_t INDICES_SIZE> 
void RawModel<COORDINATES_SIZE, INDICES_SIZE>::move(GLfloat dx, GLfloat dy, GLfloat dz)
{
	coordinates.position += glm::vec3(dx, dy, dz);
}