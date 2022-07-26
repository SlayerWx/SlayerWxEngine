#include "Model.h"
Model::Model(bool gamma) : Entity("Model"), gammaCorrection(gamma) {

    color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    ambient = glm::vec3(0.5, 0.5, 0.5);
    shininess = 1;

}

void Model::Draw() {
    for (unsigned int i = 0; i < structure.meshes.size(); i++) {
        structure.meshes[i].Draw(model,color,ambient,shininess);
    }
}


