#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures) : Entity("Entity")
{

	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	renderer->SetupMesh(vao, vbo, ebo, vertices, indices);
}

void Mesh::Draw(glm::mat4 parentModel,float &shininess) 
{
    BoundingBox aux;
    aux = CalculateBoundingBox();
    renderer->DrawBoundingBox(glm::vec3(aux.min.x,aux.min.y,aux.min.z), glm::vec3(aux.max.x, aux.max.y, aux.max.z));
	renderer->DrawMesh(vao, indices.size(), parentModel, textures, shininess);
}

BoundingBox Mesh::CalculateBoundingBox()
{
    BoundingBox bbox;

    if (vertices.empty()) {
        bbox.min = { 0.0f, 0.0f, 0.0f };
        bbox.max = { 0.0f, 0.0f, 0.0f };
        return bbox;
    }

    bbox.min = vertices[0].position;
    bbox.max = vertices[0].position;

    for (const auto& vertex : vertices) {
        bbox.min.x = std::min(bbox.min.x, vertex.position.x);
        bbox.min.y = std::min(bbox.min.y, vertex.position.y);
        bbox.min.z = std::min(bbox.min.z, vertex.position.z);
        bbox.max.x = std::max(bbox.max.x, vertex.position.x);
        bbox.max.y = std::max(bbox.max.y, vertex.position.y);
        bbox.max.z = std::max(bbox.max.z, vertex.position.z);
        
    }

    return bbox;
}