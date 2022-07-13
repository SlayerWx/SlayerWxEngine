#include "Light.h"
std::list<Light*> SlayerWxEngine_API lights;
Light::Light(glm::vec3 pos, glm::vec3 colour, glm::vec3 ambien, glm::vec3 diffu, glm::vec3 specul)
{
	position = pos;
	color = colour;
	ambient = ambien;
	diffuse = diffu;
	specular = specul;
	lights.push_back(this);
}

Light::~Light()
{
	lights.remove(this);
}
