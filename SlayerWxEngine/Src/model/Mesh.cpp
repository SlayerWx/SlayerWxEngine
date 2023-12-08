#include "Mesh.h"
static int a = 0;
Mesh::Mesh() : Entity("Entity")
{
    //vertices.clear();
    //indices.clear();
    //textures.clear();
    canDraw = true;
    imParent = false;
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures, glm::vec3 firstNormal) : Entity("Entity")
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    canDraw = true;
    imParent = false;
    a = 0;
    myFirstNormal = firstNormal;
    renderer->SetupMesh(vao, vbo, ebo, vertices, indices);
}

void Mesh::Draw(float& shininess, int _a)
{
    glm::mat4 aux;
    if (parent != NULL)
    {
        aux = parent->model;
    }
    else
    {
        aux = model;
    }
    BoundingBox bbox = CalculateBoundingBox();
    if (canDraw)
    {
        renderer->draw_bbox(CalculeModelBoundingBox(bbox));
        
        renderer->DrawMesh(vao, indices.size(), model, textures, shininess);

    }
}

BoundingBox Mesh::CalculateBoundingBox()
{
    BoundingBox bbox;

    if (vertices.empty())
    {
        bbox.min = { 0.0f, 0.0f, 0.0f };
        bbox.max = { 0.0f, 0.0f, 0.0f };
        return bbox;
    }

    bbox.min = bbox.max = glm::vec3(model * glm::vec4(vertices[0].position, 1.0f));
    for (int i = 0; i < vertices.size(); i++)
    {
        glm::vec4 worldPosition = model * glm::vec4(vertices[i].position, 1.0f);
        glm::vec3 worldPos3 = glm::vec3(worldPosition);
        if (worldPos3.x < bbox.min.x) bbox.min.x = worldPos3.x;
        if (worldPos3.x > bbox.max.x) bbox.max.x = worldPos3.x;
        if (worldPos3.y < bbox.min.y) bbox.min.y = worldPos3.y;
        if (worldPos3.y > bbox.max.y) bbox.max.y = worldPos3.y;
        if (worldPos3.z < bbox.min.z) bbox.min.z = worldPos3.z;
        if (worldPos3.z > bbox.max.z) bbox.max.z = worldPos3.z;
    }
    for (const auto& child : children)
    {
        BoundingBox childBox = child->CalculateBoundingBox();

        if (childBox.min.x < bbox.min.x) bbox.min.x = childBox.min.x;
        if (childBox.max.x > bbox.max.x) bbox.max.x = childBox.max.x;
        if (childBox.min.y < bbox.min.y) bbox.min.y = childBox.min.y;
        if (childBox.max.y > bbox.max.y) bbox.max.y = childBox.max.y;
        if (childBox.min.z < bbox.min.z) bbox.min.z = childBox.min.z;
        if (childBox.max.z > bbox.max.z) bbox.max.z = childBox.max.z;
    }

    verticesBoundingBox[0] = {bbox.min.x, bbox.min.y, bbox.min.z};
    verticesBoundingBox[1] = {bbox.max.x, bbox.min.y, bbox.min.z};
    verticesBoundingBox[2] = {bbox.max.x, bbox.max.y, bbox.min.z};
    verticesBoundingBox[3] = {bbox.min.x, bbox.max.y, bbox.min.z};
    verticesBoundingBox[4] = {bbox.min.x, bbox.min.y, bbox.max.z};
    verticesBoundingBox[5] = {bbox.max.x, bbox.min.y, bbox.max.z};
    verticesBoundingBox[6] = {bbox.max.x, bbox.max.y, bbox.max.z};
    verticesBoundingBox[7] = {bbox.min.x, bbox.max.y, bbox.max.z};

    
    return bbox;
}

glm::mat4 Mesh::CalculeModelBoundingBox(BoundingBox bbox)
{
    glm::vec3 size = glm::vec3(bbox.max.x - bbox.min.x, bbox.max.y - bbox.min.y, bbox.max.z - bbox.min.z);
    glm::vec3 center = glm::vec3((bbox.min.x + bbox.max.x) / 2, (bbox.min.y + bbox.max.y) / 2, (bbox.min.z + bbox.max.z) / 2);
    glm::mat4 transform = glm::translate(glm::mat4(1), center) * glm::scale(glm::mat4(1), size);

    glm::mat4 m = model;
    m = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
    return transform;
}
// Función para rotar un punto alrededor de un pivote en 3D
glm::vec3 Mesh::RotatePointAroundPivot(const glm::vec3& point, const glm::vec3& rotation, const glm::vec3& pivot) {
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec4 rotatedPoint = rotationMatrix * glm::vec4(point - pivot, 1.0f);

    return glm::vec3(rotatedPoint) + pivot;
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