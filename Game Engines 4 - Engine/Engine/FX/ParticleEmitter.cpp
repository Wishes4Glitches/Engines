#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int particles_, std::string shaderProgram_)
{
	particleCount = ShaderHandler::GetInstance()->GetShader("ParticleShader");

	if (particleShader == 0)
	{
		Debug::Error("failed to load particles", "Emitter.cpp", __LINE__);
	}
	else
	{
		for (int i = 0; i < particles_; i++)
		{
			Particle* newParticle = new Particle(particleShader, textureID);
			float x = rand() % 10 + 1;
			float y = rand() % 10 + 1;
			float z = rand() % 10 + 1;
			glm::vec3 Random(x, y, z);
			newParticle->SetVelocity(Random);
			newParticle->SetPosition(glm::vec3(0));
			newParticle->SetLifeTime(1.0f);
			particles.push_back(newParticle);
		}
	}
}

ParticleEmitter::~ParticleEmitter()
{

}

void ParticleEmitter::Update(const float deltaTime_)
{
	for (auto i : particles)
	{
		float newLifeTime = i->GetLifeTime();
		newLifeTime -= deltaTime_;
		if (newLifeTime <= 0)
		{
			ParticleLife(i);
		}
		else
		{
			i->SetLifeTime(newLifeTime);
			glm::vec3 newVelocity = i->GetVelocity();
			glm::vec3 newPosition = i->GetPosition();

			newPosition += newVelocity * deltaTime_;
			i->SetPosition(newPosition);
		}
	}
}

void ParticleEmitter::Render(Camera* camera_)
{
	glEnable(GL_BLEND);
	glUseProgram(particleCount);
	for (auto i : particles)
	{
		i->Render(camera_);
	}
	glDisable(GL_BLEND);
}

void ParticleEmitter::ParticleLife(Particle* particle_)
{
	float x = rand() % 10 + 1;
	float y = rand() % 10 + 1;
	float z = rand() % 10 + 1;
	glm::vec3 Random(x, y, z);
	particle_->SetVelocity(Random);
	particle_->SetPosition(glm::vec3(0));
	particle_->SetLifeTime(1.0f);
}