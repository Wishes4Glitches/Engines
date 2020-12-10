#include "Component3.h"

Component3::Component3() : parent(nullptr)
{

}

Component3::~Component3()
{
	parent = nullptr;
}

bool Component3::OnCreate(GameObject* parent_)
{
	return true;
}

void Component3::Update(float deltaTime_)
{
	std::cout << "Updating Component 3" << std::endl;
}