#ifndef LIGHT_H
#define LIGHT_H
#include "export/export.h"
#include "glm/glm.hpp"

struct SlayerWxEngine_API DirectionalLight
{
	glm::vec3 direction;
	glm::vec3 color;
	float diffuseIntensity;
};
class SlayerWxEngine_API Light
{

public:
	Light();
	~Light();
	static void SetAmbientLight(float r,float g,float b);
	static glm::vec3 GetAmbientLight();
	static void SetAmbientSrength(glm::float32 newStr);
	static glm::float32 GetAmbientStrength();
	static DirectionalLight actualDirectionalLight;
	static glm::vec3 ambient;
	static float ambientStrength;
	static void SetACtualDirectionalLight(DirectionalLight dirLight);

};
#endif