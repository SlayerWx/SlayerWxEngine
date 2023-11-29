#ifndef MODELLOADER_H
#define MODELLOADER_H
#include "export/export.h"
#include "ModelStruct.h"
#include "../Lib/assimp/include/assimp/Importer.hpp"
#include "../Lib/assimp/include/assimp/scene.h"
#include "../Lib/assimp/include/assimp/postprocess.h"
#include <map>
class SlayerWxEngine_API ModelLoader
{
public:
	static void LoadModel(std::string const& path, ModelStruct& structure);


private:
	ModelLoader();
	static void ProcessRootPlane(aiNode* root, const aiScene* scene, ModelStruct& _structure);

	static Mesh* ProcessNode(aiNode* node, const aiScene* scene, ModelStruct& structure, bool isRoot);

	static void ProcessRootNode(aiNode* root, const aiScene* scene, ModelStruct& _structure);

	static Mesh* ProcessMeshForRoot(aiNode* root, const aiScene* scene, ModelStruct& _structure);

	static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene, ModelStruct& structure, bool isRoot);

	static std::vector<TextureData> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, ModelStruct& structure);

	static std::vector<Mesh*> parents;
	static std::vector<Mesh*> planeBSP;
};

#endif