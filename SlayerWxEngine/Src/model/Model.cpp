#include "Model.h"
#include "ModelLoader.h"
Model::Model() : Entity("Model") {
    shininess = 32;
    ModelLoader::LoadModel("assets/models/backpack/backpack.obj", structure);

}

void Model::Draw() {
    for (unsigned int i = 0; i < structure.meshes.size(); i++) {
        structure.meshes[i].Draw(model,shininess);
    }
}

void Model::ScaleForParts(float scaleInX,float scaleInY,float scaleInZ)
{
    for (int i = 0; i < structure.meshes.size(); i++)
    {
        if (scaleInX < 0) scaleInX = 0.1;
        if (scaleInY < 0) scaleInY = 0.1;
        if (scaleInZ < 0) scaleInZ = 0.1;
        structure.meshes[i].Scale(scaleInX, scaleInY, scaleInZ);

    }
}


