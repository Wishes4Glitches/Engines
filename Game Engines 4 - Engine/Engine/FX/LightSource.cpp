#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, glm::vec3 lightColour_, float ambientValue_, float diffuseValue_) {
	position = position_;
	ambientValue = ambientValue_;
	diffuseValue = diffuseValue_;
	lightColour = lightColour_;
}

LightSource::~LightSource()
{

}

void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::SetAmbientValue(float ambientValue_)
{
	ambientValue = ambientValue_;
}

void LightSource::SetDiffuseValue(float diffuseValue_)
{
	diffuseValue = diffuseValue_;
}

void LightSource::SetLightColour(glm::vec3 lightColour_)
{
	lightColour = lightColour_;
}

glm::vec3 LightSource::GetPosition()
{
	return position;
}

float LightSource::GetAmbientValue()
{
	return ambientValue;
}

float LightSource::GetDiffuseValue()
{
	return diffuseValue;
}

glm::vec3 LightSource::GetLightColour()
{
	return lightColour;
}