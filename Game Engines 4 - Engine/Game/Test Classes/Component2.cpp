#include "Component2.h"

Component2::Component2() : parent(nullptr)
{

}

Component2::~Component2()
{
	parent = nullptr;
}

bool Component2::OnCreate(GameObject* parent_)
{
	return true;
}

void Component2::Update(float deltaTime_)
{
	std::cout << "Updating Component 2" << std::endl;
}