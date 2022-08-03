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


