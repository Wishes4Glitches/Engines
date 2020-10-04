#include "Component2.h"

Component2::Component2() : Component()
{

}

Component2::~Component2()
{

}

bool Component2::OnCreate(GameObject* parent_)
{
	parent = parent_;
	return true;
}

void Component2::Update(float deltaTime_)
{
	std::cout << "Updating component 2" << std::endl;
}