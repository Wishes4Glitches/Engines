#include "Component3.h"

Component3::Component3() : Component()
{

}

Component3::~Component3()
{

}

bool Component3::OnCreate(GameObject* parent_)
{
	parent = parent_;
	return true;
}

void Component3::Update(float deltaTime_)
{
	std::cout << "Updating component 3" << std::endl;
}