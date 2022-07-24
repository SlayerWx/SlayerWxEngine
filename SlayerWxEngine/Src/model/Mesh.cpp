#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures) : Entity("Entity") {

	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	renderer->SetupMesh(vao, vbo, ebo, vertices, indices);
}
void Mesh::Draw(glm::mat4 parentModel, glm::vec4 &color, glm::vec3 &ambient,float &shininess) {
	renderer->DrawMesh(vao, indices.size(), parentModel, textures,color,ambient, shininess);
}