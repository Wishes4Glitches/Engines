#ifndef COMPONENT1_H
#define COMPONENT1_H

#include "../../Engine/Rendering/3D/Component.h"
#include <iostream>

class Component1 : public Component
{
public:
	Component1();
	~Component1();
	virtual bool OnCreate(GameObject* parent_);
	virtual void Update(float deltaTime_);

protected:
	GameObject* parent;
};
#endif