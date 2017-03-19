#pragma once
#include "Renderer.h"

#include <map>
#include <vector>

class MasterRenderer
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

