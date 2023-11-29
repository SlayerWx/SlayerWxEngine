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
	Model();

	void Draw();
	void SetMeshPosition(float x, float y, float z, int index);
	void SetMeshScale(float x, float y, float z, int index);
	void ScaleForParts(float scaleInX, float scaleInY, float scaleinZ);
	float shininess;
	void InfoAboutCol(float ix, float ax, float iy, float ay, float iz, float az, int index);
private:
};

#endif // !MODEL_H