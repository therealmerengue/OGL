#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(Renderer* renderer) : renderer(renderer)
{
}

void MasterRenderer::addEntity(const Entity& entity)
{
	auto entityModel = entity.getModel();

	if (entityMap.find(entityModel) == entityMap.end())
	{
		std::pair<Model*, std::vector<Entity>> p(entityModel, std::vector<Entity> { entity });
		entityMap.insert(p);
	}
	else 
	{
		entityMap.at(entityModel).push_back(entity);
	}
}

void MasterRenderer::render()
{
	renderer->render(entityMap);
}
