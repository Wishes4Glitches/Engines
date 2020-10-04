#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>

class LightSource
{
public:
	LightSource(glm::vec3 position_, glm::vec3 lightColour_, float ambientValue_, float diffuse_);
	~LightSource();

	void SetPosition(glm::vec3 position_);
	void SetAmbientValue(float ambientValue_);
	void SetDiffuseValue(float diffuseValue_);
	void SetLightColour(glm::vec3 lightColour_);

	glm::vec3 GetPosition();
	float GetAmbientValue();
	float GetDiffuseValue();
	glm::vec3 GetLightColour();

private:

	glm::vec3 position;
	float ambientValue;
	float diffuseValue;
	glm::vec3 lightColour;
};
#endif