#include "BSP.h"

BSP::BSP()
{
}

BSP::~BSP()
{
}

void BSP::AddModel(Model* newModel)
{
	models.push_back(newModel);
}

void BSP::AddPlane(BSPPlane* plane)
{
	planes.push_back(plane);

}

void BSP::RemoveModel()
{
	models.clear();
}

void BSP::CalculateBSP()
{
	glm::vec3 pos = Renderer::myRef->GetCamera()->cameraPos;
	for (int i = 0; i < models.size(); i++)
	{
		CalculateBSPMesh(models[i]->structure.meshes[1], pos);
	}
}

void BSP::CalculateBSPMesh(Mesh* mesh, glm::vec3 cameraPos)
{
	
	for (int i = 0; i < mesh->children.size(); i++)
	{
		CalculateBSPMesh(mesh->children[i], cameraPos);
	}
	for (int i = 0; i < planes.size(); i++)
	{
		if (planes[i]->FrontPlane(mesh->position) == planes[i]->FrontPlane(cameraPos))
		{
			mesh->canDraw = true;
		}
		else
		{
			mesh->canDraw = false;
			break;
		}
	}



}
