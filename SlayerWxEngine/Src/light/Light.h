#ifndef LIGHT_H
#define LIGHT_H
#include "export/export.h"
#include "glm/glm.hpp"
class SlayerWxEngine_API Light
{
public:
	Light();
	~Light();
	static void SetAmbientLight(float r,float g,float b);
	static glm::vec3 GetAmbientLight();
	static glm::vec3 ambient;
private:

};
#endif