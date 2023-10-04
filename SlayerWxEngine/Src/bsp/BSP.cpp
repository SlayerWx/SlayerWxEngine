#include "BSP.h"

BSP::BSP()
{
	models = new std::vector<Model*>();
}

BSP::~BSP()
{
	if (models != NULL) delete models;
}

void BSP::AddModel(Model* newModel)
{
	models->push_back(newModel);
}

void BSP::AddPlane(BSPPlane& plane)
{
	planes->push_back(plane);

}

void BSP::RemoveModel()
{
	models->clear();
}

void BSP::CalculateBSPMesh(Mesh* mesh, bool isRoot) {
   // if (!isRoot) {
   //
   //     bool checkPassed = true;
   //     std::cout << std::endl;
   //
   //     if (mesh->GetIsParent()) {
   //         for (int i = 0; i < _planes.size(); i++) {
   //             glm::vec3 dirA = glm::normalize(mesh->GetMinCollGeneral() - _planes[i].model->transform.position);
   //             float dotProdA = glm::dot(dirA, _planes[i].model->transform.forward);
   //
   //             glm::vec3 dirB = glm::normalize(mesh->GetMaxCollGeneral() - _planes[i].model->transform.position);
   //             float dotProdB = glm::dot(dirB, _planes[i].model->transform.forward);
   //
   //             if (dotProdA < 0.0f && dotProdB < 0.0f) {
   //                 std::cout << "mesh : " << mesh->GetName() << " dont pass general check!" << std::endl;
   //                 checkPassed = false;
   //                 break;
   //             }
   //         }
   //
   //         if (!checkPassed) {
   //             mesh->SetCanDrawMesh(false);
   //             mesh->StopDrawMeshAndSons(mesh);
   //             return;
   //         }
   //         else
   //             std::cout << "mesh: " << mesh->GetName() << " pass general check!" << std::endl;
   //     }
   //     else
   //         std::cout << "mesh : " << mesh->GetName() << " has 0 sons, dont make general check!" << std::endl;
   //
   //
   //     for (int i = 0; i < _planes.size(); i++) {
   //         glm::vec3 dirA = glm::normalize(mesh->GetMinColl() - _planes[i].model->transform.position);
   //         float dotProdA = glm::dot(dirA, _planes[i].model->transform.forward);
   //
   //         glm::vec3 dirB = glm::normalize(mesh->GetMaxColl() - _planes[i].model->transform.position);
   //         float dotProdB = glm::dot(dirB, _planes[i].model->transform.forward);
   //
   //         if (dotProdA < 0.0f && dotProdB < 0.0f) {
   //             checkPassed = false;
   //             break;
   //         }
   //     }
   //
   //     if (!checkPassed) {
   //         mesh->SetCanDrawMesh(false);
   //         std::cout << "mesh: " << mesh->GetName() << " dont pass own check!" << std::endl;
   //     }
   //     else {
   //         mesh->SetCanDrawMesh(true);
   //         std::cout << "mesh: " << mesh->GetName() << " pass own check!" << std::endl;
   //     }
   // }
   //
   // for (int i = 0; i < mesh->GetMeshesSons().size(); i++)
   //     CalculateBSPMesh(mesh->GetMeshesSons()[i], false);






}
