#ifndef MESH_H
#define MESH_H

#include "entity/Entity.h"
#include "export/export.h"
#include "TextureImporter/TextureImporter.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>
#include <vector>
struct BoundingBox {
	glm::vec3 min;
	glm::vec3 max;
};
class SlayerWxEngine_API Mesh : public Entity {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures);

	
	void Draw(glm::mat4 parentModel, float &shinies);


	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureData> textures;

	BoundingBox CalculateBoundingBox();
	unsigned int vao;

private:
	unsigned int ebo, vbo;

};

#endif // !MESH_H