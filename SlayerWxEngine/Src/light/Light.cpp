#include "Light.h"
glm::vec3 Light::ambient = glm::vec3(1.0f,1.0f,1.0f);

//void Light::SetAmbientLight(float r, float g, float b)
//{
//	ambient = glm::vec3(r, g, b);
//}
//glm::vec3 Light::GetAmbientLight()
//{
//	return glm::vec3(1.0f, 1.0f, 1.0f); // ambient;
//}

Light::Light()
{
}

Light::~Light()
{
}

void Light::SetAmbientLight(float r, float g, float b)
{
	ambient = glm::vec3(r,g,b);
}

glm::vec3 Light::GetAmbientLight()
{
	return glm::vec3();
}
