#include "Particle.h"

Particle::Particle(GLuint shaderProgram_, GLuint textureID_) : VAO(0), VBO(0)
{
	particleColour = shaderProgram_;
	size = 5;
	velocity = glm::vec3(1.5f);
	colour = glm::vec3(1, 0, 0);
	GenerateBuffers();
}

Particle::~Particle()
{

}

void Particle::Update(const float deltaTime_)
{
	lifeTime -= deltaTime_;
	position = deltaTime_ * velocity;
}

void Particle::Render(Camera* camera_)
{
	glEnable(GL_PROGRAM_POINT_SIZE);
	glm::mat4 model;

	model = glm::translate(model, glm::vec3(position.x, position.y, position.z));

	glUniform3fv(colourLoc, 1, glm::value_ptr(colour));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform1f(pointSize, size);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
	glDisable(GL_PROGRAM_POINT_SIZE);
}

void Particle::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindVertexArray(0);

	modelLoc = glGetUniformLocation(particleColour, "model");
	projLoc = glGetUniformLocation(particleColour, "proj");
	viewLoc = glGetUniformLocation(particleColour, "view");
	colourLoc = glGetUniformLocation(particleColour, "tintColour");
	pointSize = glGetUniformLocation(particleColour, "Size");
}