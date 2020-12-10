#ifndef SPRITESURFACE_H
#define SPRITESURFACE_H

#include <glew.h>
#include <glm/glm.hpp>
#include <string>
#include "../../Camera/Camera.h"

struct Vertex2D
{
	glm::vec2 position;
	glm::vec2 textureCoords;
};

class SpriteSurface
{
public:
	SpriteSurface(std::string imageName_, float imageScale_, float imageAngle_, glm::vec4 imageTintColor_);
	~SpriteSurface();

	void Draw(Camera* camera_, Vertex2D* position_);

	void GetSurfaceWidth();
	void GetSurfaceHeight();
private:



	GLuint VAO, VBO;
};
#endif