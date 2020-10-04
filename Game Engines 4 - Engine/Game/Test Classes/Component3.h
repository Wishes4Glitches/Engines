#ifndef COMPONENT3_H
#define COMPONENT3_H

#include "../../Engine/Rendering/3D/Component.h"
#include <iostream>

class Component3 : public Component
{
public:
	Component3();
	~Component3();
	bool OnCreate(GameObject* parent_);
	void Update(float deltaTime_);
};
#endif