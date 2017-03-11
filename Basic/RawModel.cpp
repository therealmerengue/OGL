#include "RawModel.h"

RawModel::~RawModel()
{
	glDeleteVertexArrays(1, &vaoID);

	for (size_t i = 0; i < vbosAndEbos.size(); i++)
		glDeleteBuffers(1, &vbosAndEbos[i]);
}

GLuint RawModel::getVaoID() const
{
	return vaoID;
}

void RawModel::rotate(GLfloat angle)
{
	coordinates.rotationAngle += angle;
}

void RawModel::move(GLfloat dx, GLfloat dy, GLfloat dz)
{
	coordinates.position += glm::vec3(dx, dy, dz);
}