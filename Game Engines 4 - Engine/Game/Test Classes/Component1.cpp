#include "Component1.h"

Component1::Component1() : parent(nullptr)
{

}

Component1::~Component1()
{
	parent = nullptr;
}

bool Component1::OnCreate(GameObject* parent_)
{
	return true;
}

void Component1::Update(float deltaTime_)
{
	std::cout << "Updating Component 1" << std::endl;
}