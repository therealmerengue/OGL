#include "BasicModelBuilder.h"

BasicModelBuilder::BasicModelBuilder(Dimensions dim)
{
	switch (dim)
	{
	case Dimensions::dim2D:
		model = mb.InitBuild()
			->Vertices(vertices2D)
			->VertexColors(vertexColors2D)
			->Indices(indices2D)
			->Result();
		break;
	case Dimensions::dim3D:
		model = mb.InitBuild()
			->Vertices(vertices3D)
			->VertexColors(vertexColors3D)
			->Indices(indices3D)
			->Result();
		break;
	default:
		break;
	}
}

BasicModelBuilder::BasicModelBuilder(Dimensions dim, const Texture& texture)
{
	switch (dim)
	{
	case Dimensions::dim2D:
		model = mb.InitBuild()
			->Vertices(vertices2D)
			->TextureCoords(textureCoords)
			->Tex(texture)
			->Indices(indices2D)
			->Result();
		break;
	case Dimensions::dim3D:
		model = mb.InitBuild()
			->Vertices(vertices3D)
			->TextureCoords(textureCoords)
			->Tex(texture)
			->Indices(indices3D)
			->Result();
		break;
	default:
		break;
	}
}

std::shared_ptr<Entity> BasicModelBuilder::Result(glm::vec3 position, glm::vec3 scale,
	glm::vec3 rotations, glm::vec3 color)
{
	return std::make_shared<Entity>(model, position, scale, rotations, color);
}
