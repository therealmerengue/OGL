#pragma once
#include "Model.h"
#include "Texture.h"

#include <memory>
#include <vector>

class ModelBuilder
{
private:
	std::shared_ptr<Model> model;

	GLuint createAndBindVAO();
	void bindVAO(GLuint vaoID);
	void unbindVAO();
	void storeDataInAttributeList(GLenum bufferType, int attributeNumber, int coordinateSize, GLenum type, int stride, int offset,
		const std::vector<GLfloat>& data);
	void storeVertexIndices(const std::vector<GLuint>& indices);

public:
	ModelBuilder() {}

	ModelBuilder* Vertices(const std::vector<GLfloat>& vertices);
	ModelBuilder* VertexColors(const std::vector<GLfloat>& vertexColors);
	ModelBuilder* Indices(const std::vector<GLuint>& indices);
	ModelBuilder* TextureCoords(const std::vector<GLfloat>& texCoords);
	ModelBuilder* Tex(const Texture& texture);
	ModelBuilder* Normals(const std::vector<GLfloat>& normals);
	ModelBuilder* InitBuild();
	std::shared_ptr<Model> Result();
};
