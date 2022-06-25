#ifndef LIGHT_H
#define LIGHT_H
#include "export/export.h"
#include "glm/glm.hpp"

struct SlayerWxEngine_API DirectionalLight
{
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color;
	float diffuseIntensity;
};
struct SlayerWxEngine_API SpotLight
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 direction;
	float specularIntensity;
	float shininess;
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
	static SpotLight actualSpotLight;
	static glm::vec3 ambient;
	static float ambientStrength;
	static void SetActualDirectionalLight(DirectionalLight dirLight);
	static void SetActualSpotLight(SpotLight spot);

};
#endif