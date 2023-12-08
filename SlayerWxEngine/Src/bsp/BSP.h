#ifndef BSP_H
#define BSP_H

#include "BspPlane.h"
#include "model/Model.h"
class SlayerWxEngine_API BSP
{
public:
	static std::vector<Model*> models;
	static std::vector<Mesh*> planes;
	static void AddModel(Model* newModel);
	static void AddPlane(Mesh* plane);
	static void RemoveModel();
	static void CalculateBSP();
	static void CalculateBSPMesh(Mesh* mesh, glm::vec3 cameraPos);
	static float GetDistanceToPoint(glm::vec3 positionPlane, glm::vec3 normalPlane,glm::vec3 point);
	static bool FrontPlane(glm::vec3 positionPlane, glm::vec3 normalPlane,glm::vec3 point);
	static void DrawPlanes();
private:
	BSP();
	~BSP();

};

#endif