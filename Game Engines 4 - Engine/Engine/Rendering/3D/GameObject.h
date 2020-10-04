#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "Component.h"

class GameObject
{
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();
	void Render(Camera* camera_);
	void Update(const float deltaTime_);

	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	BoundingBox GetBoundingBox() const;
	std::string GetTag() const;
	bool GetHit() const;

	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);

	template <typename T>
	void AddComponent();
	template <typename U>
	U* GetComponent();
	template <typename V>
	void RemoveComponent();
private:
	Model* model;
	int modelInstance;

	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;

	BoundingBox box;

	std::string tag;
	bool hit;

	std::vector<Component*> objects;
	int i = 0;
};
#endif 