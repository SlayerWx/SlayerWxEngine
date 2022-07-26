#ifndef MODEL_H
#define MODEL_H
#include "export/export.h"
#include "ModelStruct.h"
#include "../Lib/assimp/include/assimp/Importer.hpp"
#include "../Lib/assimp/include/assimp/scene.h"
#include "../Lib/assimp/include/assimp/postprocess.h"
#include <map>

class SlayerWxEngine_API Model : public Entity {
public:
	ModelStruct structure;
	bool gammaCorrection;

	Model(bool gamma = false);

	void Draw();

	glm::vec4 color;
	glm::vec3 ambient;
	float shininess;
	

private:
};

#endif // !MODEL_H