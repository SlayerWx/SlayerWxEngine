#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures) : Entity("Entity") {

	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	renderer->SetupMesh(vao, vbo, ebo, vertices, indices);
}
void Mesh::Draw(glm::mat4 parentModel,float &shininess) {
	renderer->DrawMesh(vao, indices.size(), parentModel, textures, shininess);
}