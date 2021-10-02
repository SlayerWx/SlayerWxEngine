#ifndef ENTITY_H
#define ENTITY_H
#include "export/export.h"
#include "renderer/renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class SlayerWxEngine_API Entity 
{
protected:
	glm::mat4 model;
	glm::mat4 translate;
	glm::mat4 rotateX;
	glm::mat4 rotateY;
	glm::mat4 rotateZ;
	glm::mat4 scale;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 localScale;

	// size/distance in window
	glm::mat4 projection = glm::ortho(-800.0f,800.0f,-600.0f,600.0f,100.0f,-100.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(-200,1,1));
	glm::mat4 mvp = projection * view;
	void UpdateModel();

	void RotateX(float x);
	void RotateY(float y);
	void RotateZ(float z);

public:
	Renderer* renderer;
	Entity();
	Entity(Renderer* renderer);

	void SetPosition(float x, float y, float z);
	void Scale(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Translate(float x, float y, float z);
};

#endif
