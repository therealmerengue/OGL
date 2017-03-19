#include "ModelBuilder.h"

std::shared_ptr<Model> ModelBuilder::Result()
{
	return model;
}

ModelBuilder* ModelBuilder::Vertices(const std::vector<GLfloat>& vertices)
{
	bindVAO(model->vaoID);
	model->vertices = vertices;
	storeDataInAttributeList(GL_ARRAY_BUFFER, 0, 3, GL_FLOAT, 3, 0, vertices);
	unbindVAO();
	return this;
}

ModelBuilder* ModelBuilder::VertexColors(const std::vector<GLfloat>& vertexColors)
{
	bindVAO(model->vaoID);
	model->vertexColors = vertexColors;
	storeDataInAttributeList(GL_ARRAY_BUFFER, 1, 3, GL_FLOAT, 3, 0, vertexColors);
	unbindVAO();
	return this;
}

ModelBuilder* ModelBuilder::Indices(const std::vector<GLuint>& indices)
{
	bindVAO(model->vaoID);
	model->indices = indices;
	storeVertexIndices(indices);
	unbindVAO();
	return this;
}

ModelBuilder* ModelBuilder::TextureCoords(const std::vector<GLfloat>& texCoords)
{
	bindVAO(model->vaoID);
	model->textureCoords = texCoords;
	storeDataInAttributeList(GL_ARRAY_BUFFER, 1, 2, GL_FLOAT, 2, 0, texCoords);
	unbindVAO();
	return this;
}

ModelBuilder* ModelBuilder::Tex(const Texture& texture)
{
	model->texture = texture;
	return this;
}

ModelBuilder* ModelBuilder::Normals(const std::vector<GLfloat>& normals)
{
	bindVAO(model->vaoID);
	model->normals = normals;
	storeDataInAttributeList(GL_ARRAY_BUFFER, 2, 3, GL_FLOAT, 3, 0, normals);
	unbindVAO();
	return this;
}

ModelBuilder* ModelBuilder::InitBuild()
{
	int vaoID = createAndBindVAO();
	model = std::make_shared<Model>(vaoID);
	return this;
}

GLuint ModelBuilder::createAndBindVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void ModelBuilder::bindVAO(GLuint vaoID)
{
	glBindVertexArray(vaoID);
}

void ModelBuilder::unbindVAO()
{
	glBindVertexArray(0);
}

void ModelBuilder::storeDataInAttributeList(GLenum bufferType, int attributeNumber, int coordinateSize, GLenum type, int stride, int offset,
	const std::vector<GLfloat>& data)
{
	GLuint vboID;
	model->vbosAndEbos.push_back(vboID);
	glGenBuffers(1, &vboID);
	glBindBuffer(bufferType, vboID);
	glBufferData(bufferType, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, type, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
	glEnableVertexAttribArray(attributeNumber);
	glBindBuffer(bufferType, 0);
}

void ModelBuilder::storeVertexIndices(const std::vector<GLuint>& indices)
{
	GLuint eboID;
	model->vbosAndEbos.push_back(eboID);
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}