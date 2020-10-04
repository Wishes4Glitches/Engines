#include "Component1.h"

Component1::Component1() : Component()
{

}

Component1::~Component1()
{

}

bool Component1::OnCreate(GameObject* parent_)
{
	parent = parent_;
	return true;
}

void Component1::Update(float deltaTime_)
{
	std::cout << "Updating component 1" << std::endl;
}