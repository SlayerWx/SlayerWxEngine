#ifndef MODELSTRUCT_H
#define MODELSTRUCT_H
#include <export/export.h>
#include "textureImporter/TextureImporter.h"
#include "Mesh.h"
#include <vector>
struct ModelStruct
{
	std::vector<TextureData> textures_loaded;
	std::vector<Mesh*> meshes;
	std::string directory;
	Mesh* parentMesh;
};
#endif