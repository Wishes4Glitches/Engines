#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include "../../Engine/Rendering/3D/Component.h"
#include "../Test Classes/Component1.h"
#include "../Test Classes/Component2.h"
#include "../Test Classes/Component3.h"
#include <glm/gtx/string_cast.hpp>

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();
	virtual void Draw();
private:
};
#endif