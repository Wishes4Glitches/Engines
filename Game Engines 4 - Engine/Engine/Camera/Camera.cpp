#include "Camera.h"
#include "../Core/CoreEngine.h"

std::vector<LightSource*> Camera::lights = std::vector<LightSource*>();

Camera::Camera() : position(glm::vec3())
{
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstance()->GetWindowSize().x / CoreEngine::GetInstance()->GetWindowSize().y, nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetWindowSize().x, 0.0f, CoreEngine::GetInstance()->GetWindowSize().y, -1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera()
{
	OnDestroy();
}

void Camera::OnDestroy() {
	if (lights.size() > 0) {
		for (auto l : lights) {
			delete l;
			l = nullptr;
		}
	}
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVectors();
}

glm::mat4 Camera::GetView() const
{
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetPerspective() const
{
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec3 Camera::GetCameraPosition() const
{
	return position;
}

glm::vec2 Camera::GetClippingPlanes() const
{
	return glm::vec2(nearPlane, farPlane);
}

void Camera::AddLightSource(glm::vec3 position_, glm::vec3 color_, float ambient_, float diffuse_) {
	LightSource* l = new LightSource(position_, color_, ambient_, diffuse_);
	lights.push_back(l);
}

std::vector<LightSource*> Camera::GetLightSources() {
	return lights;
}



void Camera::ProcessMouseMovement(glm::vec2 offset_)
{
	offset_ *= 0.05f;

	yaw += offset_.x;
	pitch += offset_.y;

	if (pitch > 89.9f)
	{
		pitch = 89.9f;
	}

	if (pitch < -89.9f)
	{
		pitch = -89.9f;
	}

	if (yaw < 0.0f)
	{
		yaw += 360.0f;
	}

	if (yaw > 360.0f)
	{
		yaw -= 360.0f;
	}

	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(int y_)
{
	if (y_ < 0 || y_ > 0)
	{
		position += static_cast<float>(y_) * (forward * 2.0f);
	}

	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));
}