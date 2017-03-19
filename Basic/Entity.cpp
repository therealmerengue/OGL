#include "Entity.h"

Entity::Entity(std::shared_ptr<Model> model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotations, glm::vec3 color) :
	model(model), position(position), scale(scale), rotations(rotations), color(color)
{
}

void Entity::rotate(GLfloat rx, GLfloat ry, GLfloat rz)
{
	rotations.x += rx;
	rotations.y += ry;
	rotations.z += rz;
}

void Entity::move(GLfloat dx, GLfloat dy, GLfloat dz)
{
	position += glm::vec3(dx, dy, dz);
}

void Entity::bindModelTexture() const
{
	model->bindTexture();
}
