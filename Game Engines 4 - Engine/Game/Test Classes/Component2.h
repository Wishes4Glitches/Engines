#ifndef COMPONENT2_H
#define COMPONENT2_H

#include "../../Engine/Rendering/3D/Component.h"
#include <iostream>

class Component2 : public Component
{
public:
	Component2();
	~Component2();
	bool OnCreate(GameObject* parent_);
	void Update(float deltaTime_);
};
#endif