#include "CollisionDetection.h"

#include "Ray.h"
#include "../Core/CoreEngine.h"

CollisionDetection::~CollisionDetection()
{

}

Ray CollisionDetection::ScreenPosToWorldRay(glm::vec2 mouseCoords_, glm::vec2 screenSize_, Camera* camera_)
{
	glm::vec4 rayStart_NDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, -1.0f, 1.0f);
	glm::vec4 rayEnd_NDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, 0.0f, 1.0f);

	glm::mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());

	glm::vec4 rayStart_World = inverse * rayStart_NDC;
	rayStart_World /= rayStart_World.w;

	glm::vec4 rayEnd_World = inverse * rayEnd_NDC;
	rayEnd_World /= rayEnd_World.w;

	glm::vec3 rayDir_World(rayEnd_World - rayStart_World);
	rayDir_World = glm::normalize(rayDir_World);
		
	return Ray(glm::vec3(rayStart_World), rayDir_World);
}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_)
{
	float tMin = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().x;
	float tMax = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().y;

	glm::vec3 obbPosition_World(box_->gameTransform[3].x, box_->gameTransform[3].y, box_->gameTransform[3].z);

	glm::vec3 delta = obbPosition_World - ray_->origin;

	//X Axis
	glm::vec3 xAxis(box_->gameTransform[0].x, box_->gameTransform[0].y, box_->gameTransform[0].z);
	float e = glm::dot(xAxis, delta);
	float f = glm::dot(ray_->direction, xAxis);

	if (fabs(f) > 0.001f)
	{
		float t1 = (e + box_->minVert.x) / f;
		float t2 = (e + box_->maxVert.x) / f;

		if (t1 > t2)
		{
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax)
		{
			tMax = t2;
		}

		if (t1 > tMin)
		{
			tMin = t1;
		}

		if (tMax < tMin)
		{
			return false;
		}
	}
	else
	{
		if (-e + box_->minVert.x > 0.0f || -e + box_->maxVert.x < 0.0f)
		{
			return false;
		}
	}

	//Y axis
	/*glm::vec3 yAxis(box_->transform[0].x, box_->transform[0].y, box_->transform[0].z);
	float g = glm::dot(yAxis, delta);
	float h = glm::dot(ray_->direction, yAxis);

	if (fabs(h) > 0.001f)
	{
		float t3 = (g + box_->minVert.y) / h;
		float t4 = (g + box_->maxVert.y) / h;

		if (t3 > t4)
		{
			float w2 = t3;
			t3 = t4;
			t4 = w2;
		}

		if (t4 < tMax)
		{
			tMax = t4;
		}

		if (t3 > tMin)
		{
			tMin = t3;
		}

		if (tMax < tMin)
		{
			return false;
		}
	}
	else
	{
		if (-g + box_->minVert.y > 0.0f || -g + box_->maxVert.y < 0.0f)
		{
			return false;
		}
	}

	//Z axis
	glm::vec3 zAxis(box_->transform[0].x, box_->transform[0].y, box_->transform[0].z);
	float i = glm::dot(zAxis, delta);
	float j = glm::dot(ray_->direction, zAxis);

	if (fabs(j) > 0.001f)
	{
		float t5 = (i + box_->minVert.z) / j;
		float t6 = (i + box_->maxVert.z) / j;

		if (t5 > t6)
		{
			float w3 = t5;
			t5 = t6;
			t6 = w3;
		}

		if (t6 < tMax)
		{
			tMax = t6;
		}

		if (t5 > tMin)
		{
			tMin = t5;
		}

		if (tMax < tMin)
		{
			return false;
		}
	}
	else
	{
		if (-i + box_->minVert.z > 0.0f || -i + box_->maxVert.z < 0.0f)
		{
			return false;
		}
	}*/

	ray_->intersectionDist = tMin;
	return true;
}