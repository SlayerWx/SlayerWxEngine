#ifndef LIGHT_H
#define LIGHT_H
#include "export/export.h"
#include "glm/glm.hpp"
#include <list>
//struct SlayerWxEngine_API DirectionalLight
//{
//	glm::vec3 position;
//	glm::vec3 direction;
//	glm::vec3 color;
//	float diffuseIntensity;
//};
//struct SlayerWxEngine_API SpotLight
//{
//	glm::vec3 position;
//	glm::vec3 color;
//	glm::vec3 direction;
//	glm::vec3 diffuse;
//	glm::vec3 specular;
//	float specularIntensity;
//	float shininess;
//};

class SlayerWxEngine_API Light
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light(glm::vec3 pos, glm::vec3 colour, glm::vec3 ambien, glm::vec3 diffu, glm::vec3 specul);
	~Light();

};
extern std::list<Light*> SlayerWxEngine_API lights;
#endif