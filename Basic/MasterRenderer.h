#pragma once
#include "Renderer.h"

#include <map>
#include <vector>

class MasterRenderer //for rendering multiple entities with the same model
{
private:
	Renderer* renderer;
	std::map<Model*, std::vector<Entity>> entityMap;

public:
	MasterRenderer(Renderer* renderer);
	~MasterRenderer() {}

	void addEntity(const Entity& entity);
	void render();
};

