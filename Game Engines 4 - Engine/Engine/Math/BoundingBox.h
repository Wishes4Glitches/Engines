#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>

struct BoundingBox
{
public:
	glm::vec3 minVert, maxVert;
	glm::mat4 gameTransform;

	BoundingBox()
	{
		minVert = glm::vec3();
		maxVert = glm::vec3();
		gameTransform = glm::mat4();
	}

	inline BoundingBox(glm::vec3 minVert_, glm::vec3 maxVert_, glm::mat4 gameTransform_)
	{
		minVert = minVert_;
		maxVert = maxVert_;
		gameTransform = gameTransform_;
	}

	inline bool Intersects(BoundingBox* box_) {
		glm::vec3 minCorner = GetTransformedPoint(minVert, gameTransform);
		glm::vec3 maxCorner = GetTransformedPoint(maxVert, gameTransform);

		glm::vec3 otherMinCorner = GetTransformedPoint(box_->minVert, box_->gameTransform);
		glm::vec3 otherMaxCorner = GetTransformedPoint(box_->maxVert, box_->gameTransform);

		//return result of min and max corner and other min and max corner
		return true;
	}

private:
	inline glm::vec3 GetTransformedPoint(glm::vec3 point_, glm::mat4 transform_) {
		return glm::vec3(transform_[3].x, transform_[3].y, transform_[3].z) + point_;
	}
};
#endif