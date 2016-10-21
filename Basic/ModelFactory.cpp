#include "ModelFactory.h"

ModelFactory::ModelFactory()
{
}

ModelFactory::~ModelFactory()
{
	for (int i = 0; i < vaos.size(); i++)
		glDeleteVertexArrays(1, &vaos[i]);

	for (int i = 0; i < vbos.size(); i++)
		glDeleteBuffers(1, &vbos[i]);
}

GLuint ModelFactory::createAndBindVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

void ModelFactory::unbindVAO()
{
	glBindVertexArray(0);
}
