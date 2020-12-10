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

//private:
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

	template <typename TComponent, typename ... Args>
	void AddComponent(Args&& ... args_)
	{
		TComponent* tComponentPTR = new TComponent(std::forward<Args>(args_)...);
		std::cout << "adding component \n";

		if (dynamic_cast<Component*>(tComponentPTR) == nullptr)
		{
			Debug::Error("Failed to add already existing component, Deleting Components", "GameObject.cpp", __LINE__);
			delete tComponentPTR;
			tComponentPTR == nullptr;

			return;
		}

		if (GetComponent<TComponent>() != nullptr)
		{
			Debug::Error("Object is not a child of component, Deleting Components", "GameObject.cpp", __LINE__);
			delete tComponentPTR;
			tComponentPTR == nullptr;

			return;
		}

		objects.push_back(tComponentPTR);
		tComponentPTR->OnCreate(this);
		std::cout << "Component Created" << std::endl;
	}

	template<typename TComponent>
	Component* GetComponent() {

		if (objects.size() <= 0) {
			std::cout << "Component list is empty\n";
			return nullptr;
		}

		for (auto element : objects) {

			if (dynamic_cast<TComponent*>(element) != nullptr) {
				std::cout << "return tcompptr\n";
				return element;
			}
			else {
				std::cout << "return nullptr\n";
				return nullptr;
			}
		}
	}


	template<typename TComponent>
	void RemoveComponent() {
		std::cout << "entered RemoveComponent\n";

		for (int i = 0; i < objects.size(); i++) {

			if (dynamic_cast<TComponent*>(objects[i]) != nullptr) {
				objects.erase(objects.begin() + i);
				std::cout << "Component deleted\n";
			}
		}
	}

};
#endif 