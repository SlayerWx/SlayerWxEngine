#include "Light.h"
glm::vec3 Light::ambient = glm::vec3(1.0f,1.0f,1.0f);
float Light::ambientStrength = 1.0f;
DirectionalLight Light::actualDirectionalLight;
Light::Light()
{
	actualDirectionalLight.color = glm::vec3(0.0,0.0,0.0);
	actualDirectionalLight.diffuseIntensity = 0.0;
	actualDirectionalLight.direction = glm::vec3(0.0,0.0,0.0);
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

glm::float32 Light::GetAmbientStrength()
{
	return ambientStrength;
}

void Light::SetACtualDirectionalLight(DirectionalLight dirLight)
{
	actualDirectionalLight = dirLight;
}

void Light::SetAmbientSrength(glm::float32 newStr)
{
	ambientStrength = newStr;
}
