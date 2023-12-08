#ifndef MESH_H
#define MESH_H

#include "entity/Entity.h"
#include "export/export.h"
#include "TextureImporter/TextureImporter.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>
#include <vector>
#include <array>
struct BoundingBox {
	glm::vec3 min;
	glm::vec3 max;
};
struct aiNode;
class SlayerWxEngine_API Mesh : public Entity {
public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures,glm::vec3 firstNormal);

	
	void Draw(float &shinies,int _a);
	BoundingBox CalculateBoundingBox();
	void SetNode(aiNode* _myself);
	aiNode* GetNode();
	void SetParent(Mesh* _parent);
	Mesh* GetParent();
	void AddMeshSon(Mesh* newChildren);
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureData> textures;
	std::vector<Mesh*> children;
	aiNode* myself;
	Mesh* parent;
	glm::mat4 CalculeModelBoundingBox(BoundingBox bbox);
	glm::vec3 RotatePointAroundPivot(const glm::vec3& point, const glm::vec3& rotation, const glm::vec3& pivot);
	bool canDraw = true;
	bool imParent;
	virtual void SetPosition(float x, float y, float z) override;
	virtual void Scale(float x, float y, float z) override;
	void UpdateSonPos();
	void UpdateSonScale();
	std::array<glm::vec3, 8> verticesBoundingBox;
	unsigned int vao;
	bool isRoot;
	glm::vec3 myFirstNormal;
private:
	unsigned int ebo, vbo;
};

#endif // !MESH_H