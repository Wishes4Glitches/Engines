#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"
#include <vector>

class Camera
{
public:
	Camera();
	~Camera();

	void OnDestroy();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetCameraPosition() const;
	glm::vec2 GetClippingPlanes() const;

	void AddLightSource(glm::vec3 position_, glm::vec3 color_, float ambient_, float diffuse_);
	std::vector<LightSource*> GetLightSources();

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseScroll(int y_);
private:
	void UpdateCameraVectors();

	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;
	static std::vector<LightSource*> lights;
};
#endif