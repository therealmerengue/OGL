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

void Model::rotate(RotationAxis axis, GLfloat angle)
{
	switch (axis)
	{
	case RotationAxis::x:
		coordinates.rotationAngles.x += angle;
		break;
	case RotationAxis::y:
		coordinates.rotationAngles.y += angle;
		break;
	case RotationAxis::z:
		coordinates.rotationAngles.z += angle;
		break;
	default:
		break;
	}
}

void Model::rotate(GLfloat rx, GLfloat ry, GLfloat rz)
{
	coordinates.rotationAngles.x += rx;
	coordinates.rotationAngles.y += ry;
	coordinates.rotationAngles.z += rz;
}

void Model::move(GLfloat dx, GLfloat dy, GLfloat dz)
{
	coordinates.position += glm::vec3(dx, dy, dz);
}