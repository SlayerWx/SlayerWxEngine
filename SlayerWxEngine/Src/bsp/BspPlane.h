#ifndef BSPPLANE_H
#define BSPPLANE_H
#include "cube/Cube.h"

class SlayerWxEngine_API BSPPlane : public Cube
{
public:
	BSPPlane();
	BSPPlane(std::string name, const char* path,glm::vec3 inNormal);
	~BSPPlane();
	float GetDistanceToPoint(glm::vec3 point);
	bool FrontPlane(glm::vec3 point);
private:
	glm::vec3 normal;
	float distance;
};
#endif