#include "Model.h"
Model::Model() : Entity("Model")
{
    shininess = 32;

}

void Model::Draw()
{
    for (unsigned int i = 0; i < structure.meshes.size(); i++)
    {
        structure.meshes[i].Draw(model,shininess);
    }
}


