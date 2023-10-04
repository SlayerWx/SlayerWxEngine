#include "Model.h"
Model::Model() : Entity("Model")
{
    shininess = 32;

}

void Model::Draw()
{
    structure.meshes[1]->Draw(shininess);
    //for (unsigned int i = 0; i < structure.meshes.size(); i++)
    //{
    //    structure.meshes[i]->Draw(model,shininess);
    //}
}

void Model::SetMeshPosition(float x, float y, float z, int index)
{
    if (index == 0)
    {
        position = { x, y, z };
        translate = glm::translate(glm::mat4(1.0f), position);
        //structure.meshes[index]->SetPosition(x, y, z);

        UpdateModel();
    }

    structure.meshes[index]->SetPosition(x, y, z);
}

void Model::SetMeshScale(float x, float y, float z, int index)
{
    if (index == 0)
    {
        localScale = { x, y, z };
        scale = glm::scale(glm::mat4(1.0f), localScale);
        //structure.meshes[index]->Scale(x, y, z);

        UpdateModel();
    }
    structure.meshes[index]->Scale(x, y, z);
}


