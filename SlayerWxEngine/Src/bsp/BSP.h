#ifndef BSP_H
#define BSP_H

#include "BspPlane.h"
#include "model/Model.h"
class SlayerWxEngine_API BSP
{
public:
	BSP();
	~BSP();
	std::vector<Model*>* models;
	std::vector<BSPPlane>* planes;
	void AddModel(Model* newModel);
	void AddPlane(BSPPlane &plane);
	void RemoveModel();
	void CalculateBSPMesh(Mesh* mesh, bool isRoot);
private:

};

#endif