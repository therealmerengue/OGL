#include "Model.h"

#include <iostream>

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

bool Model::bindTexture() const
{
	return texture.bindTexture();
}

bool operator==(const Model & m1, const Model & m2)
{
	return m1.getVaoID() == m2.getVaoID();
}
