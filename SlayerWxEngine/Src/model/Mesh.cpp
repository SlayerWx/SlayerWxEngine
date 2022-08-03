#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures) : Entity("Entity") {

	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	renderer->SetupMesh(vao, vbo, ebo, vertices, indices);
}


void Mesh::Draw(glm::mat4 parentModel,float &shininess) {
	renderer->DrawMesh(vao, indices.size(), parentModel, textures, shininess); // escalado por model
	//renderer->DrawMesh(vao, indices.size(), model, textures, shininess); //escalado por mesh
}