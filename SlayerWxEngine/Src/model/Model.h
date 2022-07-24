#ifndef MODEL_H
#define MODEL_H
#include "export/export.h"
#include "Mesh.h"
#include "../Lib/assimp/include/assimp/Importer.hpp"
#include "../Lib/assimp/include/assimp/scene.h"
#include "../Lib/assimp/include/assimp/postprocess.h"

#include <map>

class SlayerWxEngine_API Model : public Entity {
public:
	std::vector<TextureData> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

	Model(std::string const& path, bool gamma = false);

	void Draw();

	glm::vec4 color;
	glm::vec3 ambient;
	float shininess;
	void a();
	

private:
	void LoadModel(std::string const& path);

	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<TextureData> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif // !MODEL_H