#include "Renderer.h"

void Renderer::draw(const Entity& entity)
{
	glBindVertexArray(entity.getModelVaoID());
	glDrawElements(GL_TRIANGLES, entity.getModelIndicesSize(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::setUpModelMatrix(const Entity& entity)
{
	auto entityScale = entity.getScale();
	auto entityRotations = entity.getRotations();

	shaderManager.useProgram();
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, entity.getPosition());
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f * entityScale.x, 0.5f * entityScale.y, 0.5f * entityScale.z));
	modelMatrix = glm::rotate(modelMatrix, entityRotations.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, entityRotations.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, entityRotations.z, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f * entityScale.x, -0.5f * entityScale.y, -0.5f * entityScale.z));
	modelMatrix = glm::scale(modelMatrix, entityScale);
	glUniformMatrix4fv(shaderManager.getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Renderer::setUpViewMatrix(const Camera& camera)
{
	glm::mat4 viewMatrix;
	viewMatrix = glm::rotate(viewMatrix, camera.getPitch(), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, camera.getYaw(), glm::vec3(0.0f, 1.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, camera.getRoll(), glm::vec3(0.0f, 0.0f, 1.0f));
	viewMatrix = glm::translate(viewMatrix, -camera.getPosition());
	glUniformMatrix4fv(shaderManager.getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void Renderer::setUpMatrices(const Entity& entity, const Camera& camera)
{
	setUpModelMatrix(entity);
	setUpViewMatrix(camera);
}

Renderer::Renderer(const BasicShaderManager& shaderManager, Camera* camera) :
	shaderManager(shaderManager), camera(camera)
{
}

Renderer::~Renderer()
{
}

void Renderer::clearScreen()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const Entity& entity)
{
	setUpMatrices(entity, *camera);

	draw(entity);
}

void Renderer::renderTexture(const Entity& entity)
{
	setUpMatrices(entity, *camera);

	glActiveTexture(GL_TEXTURE0);
	entity.bindModelTexture();
	
	auto entityColor = entity.getColor();
	glUniform3f(glGetUniformLocation(shaderManager.getProgramID(), "spriteColor"), entityColor.x, entityColor.y, entityColor.z);

	draw(entity);
	Texture::unbindTexture();
}

void Renderer::render(const std::map<Model*, std::vector<Entity>>& entities)
{
	for (auto it = entities.cbegin(); it != entities.cend(); ++it)
	{
		auto entities = it->second;
		auto model = it->first;
		bool textureBound = false;

			glActiveTexture(GL_TEXTURE0);
			model->bindTexture();
			textureBound = true;
		
		for (size_t i = 0; i < entities.size(); i++)
		{
			setUpMatrices(entities[i], *camera);
			auto entityColor = entities[i].getColor();
			glUniform3f(glGetUniformLocation(shaderManager.getProgramID(), "spriteColor"), entityColor.x, entityColor.y, entityColor.z);
			draw(entities[i]);
		}
		if (textureBound)
		{
			Texture::unbindTexture();
		}
	}
}
