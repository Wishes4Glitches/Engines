#include "GameObject.h"

GameObject::GameObject(Model* model_, glm::vec3 position_) : model(nullptr)
{
	model = model_;
	position = position_;
	angle = 0.0f;
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	scale = glm::vec3(1.0f);
	tag = "";
	hit = false;
	if (model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		box = model->GetBoundingBox();
		box.gameTransform = model->GetTransform(modelInstance);
	}
}

GameObject::~GameObject()
{
	model = nullptr;
	objects[0] = nullptr;
}

void GameObject::Render(Camera* camera_)
{
	if (model)
	{
		model->Render(camera_);
	}
}

void GameObject::Update(const float deltaTime_)
{
	SetAngle(angle + 0.005f);

	AddComponent<Component>();
	GetComponent<Component>();
	RemoveComponent<Component>();
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}

float GameObject::GetAngle() const
{
	return angle;
}

glm::vec3 GameObject::GetRotation() const
{
	return rotation;
}

glm::vec3 GameObject::GetScale() const
{
	return scale;
}

BoundingBox GameObject::GetBoundingBox() const
{
	return box;
}

std::string GameObject::GetTag() const
{
	return tag;
}

bool GameObject::GetHit() const
{
	return hit;
}

void GameObject::SetPosition(glm::vec3 position_)
{
	position = position_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.gameTransform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.gameTransform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.gameTransform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.gameTransform = model->GetTransform(modelInstance);
		box.minVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
		box.maxVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
	}
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
}

void GameObject::SetHit(bool hit_, int buttonType_)
{
	hit = hit_;

	if (hit)
	{
		std::cout << tag << " was hit" << std::endl;
	}
}


template <typename T>
void GameObject::AddComponent()
{
	T* temp = new T();

		if (dynamic_cast<Component*>(temp))
		{
			if (GetComponent<T>())
			{
				Debug::Error("Failed to add already existing component. Deleting Components", "GameObject.cpp", __LINE__);
				delete temp;
				return;
			}

			else if (GetComponent<T>() == nullptr)
			{
				objects.push_back(temp);
				temp->OnCreate(this);
			}
		}

		else
		{
			Debug::Error("Object is not a child of component. Deleting Components", "GameObject.cpp", __LINE__);
			delete temp;
			return;
		}
}

template<typename U>
U* GameObject::GetComponent() 
{
	for (auto c : objects)
	{
		if (dynamic_cast<U*>(c))
		{
			return dynamic_cast<U*>(c);
		}
	}
}

template<typename V>
void GameObject::RemoveComponent() 
{
	for (int i = 0; i < 5; i++)
	{
		if (dynamic_cast<V*>(i))
		{
			objects = nullptr;
			objects.erase(objects.begin() + i);
		}
	}
}