#include "BSP.h"

std::vector<Model*> BSP::models;
std::vector<Mesh*> BSP::planes;

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

void BSP::AddPlane(Mesh* plane)
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
	mesh->canDraw = true;
	for (int i = 0; i < planes.size(); i++)
	{
		bool cameraIsFront = /*planes[i]->*/FrontPlane(planes[i]->position + planes[i]->verticesBoundingBox[0], planes[i]->myFirstNormal, cameraPos);
		//glm::vec3(model * glm::vec4(vertices[0].position, 1.0f));
		int verticesInFrontCount = 0;
		
		for (const glm::vec3 aux : mesh->verticesBoundingBox) {

			if (/*planes[i]->*/ FrontPlane(planes[i]->position + planes[i]->verticesBoundingBox[0], planes[i]->myFirstNormal, aux) != cameraIsFront) {
				verticesInFrontCount++;
				if (verticesInFrontCount >= 8) {
					mesh->canDraw = false;
					break;
				}
			}
		}
	}


}

float BSP::GetDistanceToPoint(glm::vec3 positionPlane, glm::vec3 normalPlane,glm::vec3 point)
{
	// distancia positiva si el punto esta frente al plano
	// distancia negativa si el punto esta espaldas al plano

	glm::vec3 aux;
	aux.x = normalPlane.x * 2;
	aux.y = normalPlane.y * 2;
	aux.z = normalPlane.z * 2;

	return  (glm::dot(point - positionPlane, normalPlane)+1) / (aux.x + aux.y + aux.z);

}

bool BSP::FrontPlane(glm::vec3 positionPlane,glm::vec3 normalPlane,glm::vec3 point)
{
	if (GetDistanceToPoint(positionPlane, normalPlane,point) > 0.0f)
		return true;
	return false;
}

void BSP::DrawPlanes()
{
	for (int i = 0; i < planes.size(); i++)
	{
		float aux = 0.1;
		planes[i]->Draw(aux,1);
	}
}