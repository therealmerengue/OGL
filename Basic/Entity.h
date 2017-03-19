#pragma once
#include <glm\glm.hpp>

#include "Model.h"

#include <memory>

class Entity
{
private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotations;
	glm::vec3 color;

	std::shared_ptr<Model> model;

public:
	Entity(std::shared_ptr<Model> model, glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 rotations = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	~Entity() {}

	void rotate(GLfloat rx, GLfloat ry, GLfloat rz);
	void move(GLfloat dx, GLfloat dy, GLfloat dz);

	void bindModelTexture() const;

	GLuint getModelVaoID() const { return model->getVaoID(); }
	size_t getModelIndicesSize() const { return model->getIndicesSize(); }
	glm::vec3 getPosition() const { return position; }
	glm::vec3 getScale() const { return scale; }
	glm::vec3 getRotations() const { return rotations; }
	glm::vec3 getColor() const { return color; }

	Model* getModel() const { return model.get(); }
};

