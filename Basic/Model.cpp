#include "Model.h"

Model::~Model()
{
	glDeleteVertexArrays(1, &vaoID);

	for (size_t i = 0; i < vbosAndEbos.size(); i++)
		glDeleteBuffers(1, &vbosAndEbos[i]);
}

GLuint Model::getVaoID() const
{
	return vaoID;
}

void Model::rotate(GLfloat angle)
{
	coordinates.rotationAngle += angle;
}

void Model::move(GLfloat dx, GLfloat dy, GLfloat dz)
{
	coordinates.position += glm::vec3(dx, dy, dz);
}