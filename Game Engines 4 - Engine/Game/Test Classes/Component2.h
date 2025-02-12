#ifndef COMPONENT2_H
#define COMPONENT2_H

#include "../../Engine/Rendering/3D/Component.h"
#include <iostream>

class Component2 : public Component
{
public:
	Component2();
	~Component2();
	virtual bool OnCreate(GameObject* parent_);
	virtual void Update(float deltaTime_);

protected:
	GameObject* parent;
};
#endif