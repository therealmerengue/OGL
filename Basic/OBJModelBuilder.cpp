#include "OBJModelBuilder.h"
#include "Texture.h"

#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> OBJModelBuilder::split(const std::string& s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while (std::getline(ss, item, delim)) 
		tokens.push_back(item);
	return tokens;
}

void OBJModelBuilder::alignTexturesAndNormals(const std::vector<std::string>& vertexData, const std::vector<glm::vec2>& textureCoords, const std::vector<glm::vec3>& normals)
{
	GLuint currentVertexPointer = std::stoi(vertexData[0]) - 1;
	indices.push_back(currentVertexPointer);
	glm::vec2 currentTex = textureCoords.at(std::stoi(vertexData[1]) - 1);
	alignedTextureCoords[currentVertexPointer * 2] = currentTex.x;
	alignedTextureCoords[currentVertexPointer * 2 + 1] = 1 - currentTex.y;
	glm::vec3 currentNorm = normals.at(std::stoi(vertexData[2]) - 1);
	alignedNormals[currentVertexPointer * 3] = currentNorm.x;
	alignedNormals[currentVertexPointer * 3 + 1] = currentNorm.y;
	alignedNormals[currentVertexPointer * 3 + 2] = currentNorm.z;
}

OBJModelBuilder* OBJModelBuilder::loadObjModel(const std::string& modelPath)
{
	std::ifstream modelFile(modelPath);
	std::string line;

	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> textureCoords;
	
	bool firstF = true;

	while (std::getline(modelFile, line)) 
	{
		auto currentLine = split(line, ' ');
		if (line.substr(0, 2) == "v ")
			vertices.push_back(glm::vec3(std::stof(currentLine[1]), std::stof(currentLine[2]), std::stof(currentLine[3])));
		else if (line.substr(0, 2) == "vt")
			textureCoords.push_back(glm::vec2(std::stof(currentLine[1]), std::stof(currentLine[2])));
		else if (line.substr(0, 2) == "vn")
			normals.push_back(glm::vec3(std::stof(currentLine[1]), std::stof(currentLine[2]), std::stof(currentLine[3])));
		else if (line[0] == 'f')
		{
			alignedTextureCoords.resize(vertices.size() * 2);
			alignedNormals.resize(vertices.size() * 3);
			break;
		}
	}

	while (std::getline(modelFile, line))
	{
		if (line[0] != 'f')
			continue;

		auto currentLine = split(line, ' ');

		auto vertex1 = split(currentLine[1], '/');
		auto vertex2 = split(currentLine[2], '/');
		auto vertex3 = split(currentLine[3], '/');

		alignTexturesAndNormals(vertex1, textureCoords, normals);
		alignTexturesAndNormals(vertex2, textureCoords, normals);
		alignTexturesAndNormals(vertex3, textureCoords, normals);
	}

	alignedVertices.resize(vertices.size() * 3);

	int vertexPointer = 0;

	for (size_t i = 0; i < vertices.size(); i++)
	{
		alignedVertices[vertexPointer++] = vertices[i].x;
		alignedVertices[vertexPointer++] = vertices[i].y;
		alignedVertices[vertexPointer++] = vertices[i].z;
	}

	return this;
}

std::shared_ptr<Model> OBJModelBuilder::Result(const Texture& texture)
{
	auto model = builder.InitBuild()
		->Vertices(alignedVertices)
		->TextureCoords(alignedTextureCoords)
		->Normals(alignedNormals)
		->Tex(texture)
		->Indices(indices)
		->Result();

	alignedVertices.clear();
	alignedNormals.clear();
	alignedTextureCoords.clear();
	indices.clear();

	return model;
}
