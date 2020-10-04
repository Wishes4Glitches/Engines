#include "Mesh.h"

Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), modelLoc(0), viewLoc(0), projLoc(0) //textureLoc(0)
{
	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	subMesh.vertexList.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_)
{
	glUniform1i(texture, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniform3fv(viewPos, 1, glm::value_ptr(camera_->GetCameraPosition()));
	glUniform3fv(lightPosition, 1, glm::value_ptr(camera_->GetLightSources()[0]->GetPosition()));
	glUniform1f(lightAmbient, camera_->GetLightSources().at(0)->GetAmbientValue());
	glUniform1f(lightDiffuse, camera_->GetLightSources().at(0)->GetDiffuseValue());
	glUniform3fv(lightColour, 1, glm::value_ptr(camera_->GetLightSources()[0]->GetLightColour()));
	glUniform1f(matShininess, subMesh.material.shininess);
	glUniform1f(matTransparency, subMesh.material.transparency);
	glUniform3fv(matAmbient, 1, glm::value_ptr(subMesh.material.ambient));
	glUniform3fv(matDiffuse, 1, glm::value_ptr(subMesh.material.diffuse));
	glUniform3fv(matSpecular, 1, glm::value_ptr(subMesh.material.specular));

	glBindVertexArray(VAO);
	for (int i = 0; i < instances_.size(); i++)
	{
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
	glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//TEXTURE COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	//COLOUR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	//textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	viewPos = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPosition = glGetUniformLocation(shaderProgram, "light.lightPosition");
	lightAmbient = glGetUniformLocation(shaderProgram, "light.lightAmbient");
	lightDiffuse = glGetUniformLocation(shaderProgram, "light.lightDiffuse");
	lightColour = glGetUniformLocation(shaderProgram, "light.lightColour");
	matShininess = glGetUniformLocation(shaderProgram, "material.matShininess");
	matTransparency = glGetUniformLocation(shaderProgram, "material.matTransparency");
	matAmbient = glGetUniformLocation(shaderProgram, "material.matAmbient");
	matDiffuse = glGetUniformLocation(shaderProgram, "material.matDiffuse");
	matSpecular = glGetUniformLocation(shaderProgram, "material.matSpecular");
	texture = glGetUniformLocation(shaderProgram, "material.texture");
}