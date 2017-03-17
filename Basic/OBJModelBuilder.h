#pragma once
#include "Model.h"
#include "ModelBuilder.h"

#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include <glm\glm.hpp>
#include <GL\glew.h>

class OBJModelBuilder
{
private:
	std::vector<GLuint> indices;
	std::vector<float> alignedVertices, alignedNormals, alignedTextureCoords;
	ModelBuilder builder;

	std::vector<std::string> split(const std::string &s, char delim);
	void alignTexturesAndNormals(const std::vector<std::string>& vertexData, const std::vector<glm::vec2>& textureCoords, const std::vector<glm::vec3>& normals);
	
public:
	OBJModelBuilder() {}
	~OBJModelBuilder() {}
	
	OBJModelBuilder* loadObjModel(const std::string& modelPath);
	std::unique_ptr<Model> Result(const Coordinates& coordinates, const std::string& texturePath);
};

