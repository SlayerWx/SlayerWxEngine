#include "Mesh.h"

Mesh::Mesh() : Entity("Entity")
{
    //vertices.clear();
    //indices.clear();
    //textures.clear();
    canDraw = true;
    imParent = false;
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures) : Entity("Entity")
{

	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
    canDraw = true;
    imParent = false;
	renderer->SetupMesh(vao, vbo, ebo, vertices, indices);
}

void Mesh::Draw(float &shininess) 
{
    BoundingBox aux;

    if (canDraw)
    {


        aux = CalculateBoundingBox();

        renderer->DrawBoundingBox(glm::vec3(aux.min.x, aux.min.y, aux.min.z), glm::vec3(aux.max.x, aux.max.y, aux.max.z));
        renderer->DrawMesh(vao, indices.size(), model, textures, shininess);
        for (size_t i = 0; i < children.size(); i++)
        {
            children[i]->Draw(shininess);
        }

    }
}

void Mesh::SetNode(aiNode* _myself)
{
    myself = _myself;
}

aiNode* Mesh::GetNode()
{
    return myself;
}

void Mesh::SetParent(Mesh* _parent)
{
    parent = _parent;
}

Mesh* Mesh::GetParent()
{
    return parent;
}

void Mesh::AddMeshSon(Mesh* newChildren)
{
    children.push_back(newChildren);
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

void Mesh::SetPosition(float x, float y, float z) {
    localPosition = { x, y, z };

    if (parent)
        position = parent->position + localPosition;
    else
        position = localPosition;

    translate = glm::translate(glm::mat4(1.0f), position);

    for (int i = 0; i < children.size(); i++)
        children[i]->UpdateSonPos();

    UpdateModel();
}

void Mesh::Scale(float x, float y, float z) {
    meshLocalScale = { x, y, z };

    if (parent)
        localScale = parent->localScale * meshLocalScale;
    else
        localScale = meshLocalScale;

    scale = glm::scale(glm::mat4(1.0f), localScale);

    for (int i = 0; i < children.size(); i++)
        children[i]->UpdateSonScale();

    UpdateModel();
}
void Mesh::UpdateSonPos() {

    position = parent->position + localPosition;

    translate = glm::translate(glm::mat4(1.0f), position);

    for (int i = 0; i < children.size(); i++)
        children[i]->UpdateSonPos();

    UpdateModel();
}

void Mesh::UpdateSonScale() {
    localScale = parent->localScale * meshLocalScale;
    scale = glm::scale(glm::mat4(1.0f), localScale);

    for (int i = 0; i < children.size(); i++)
        children[i]->UpdateSonScale();

    UpdateModel();
}