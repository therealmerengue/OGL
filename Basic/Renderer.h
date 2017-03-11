#pragma once
#include "ShaderManager.h"
#include "RawModel.h"

#include <GL\glew.h>

class Renderer
{
private:
	ShaderManager shaderManager;

public:
	Renderer();
	~Renderer();

	void clearScreen();

	void render(const RawModel& model)
	{
		shaderManager.useProgram();
		glm::mat4 modMatrix;
		shaderManager.modelMatrix = modMatrix;
		shaderManager.modelMatrix = glm::translate(shaderManager.modelMatrix, model.coordinates.position);
		shaderManager.modelMatrix = glm::translate(shaderManager.modelMatrix, glm::vec3(0.5f * model.coordinates.size.x, 0.5f * model.coordinates.size.y, 0.5f * model.coordinates.size.z));
		shaderManager.modelMatrix = glm::rotate(shaderManager.modelMatrix, model.coordinates.rotationAngle, model.coordinates.rotationAxis);
		shaderManager.modelMatrix = glm::translate(shaderManager.modelMatrix, glm::vec3(-0.5f * model.coordinates.size.x, -0.5f * model.coordinates.size.y, -0.5f * model.coordinates.size.z));
		shaderManager.modelMatrix = glm::scale(shaderManager.modelMatrix, model.coordinates.size);

		glUniformMatrix4fv(shaderManager.modelMatLocation, 1, GL_FALSE, glm::value_ptr(shaderManager.modelMatrix));
		glBindVertexArray(model.vaoID);
		glDrawElements(GL_TRIANGLES, model.getIndicesSize(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};

