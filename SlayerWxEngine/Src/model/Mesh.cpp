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

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures) : Entity("Entity")
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
    canDraw = true;
    imParent = false;
    a = 0;
	renderer->SetupMesh(vao, vbo, ebo, vertices, indices);
}

void Mesh::Draw( float &shininess,int _a) 
{ 
    if (canDraw)
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
        renderer->draw_bbox(vertices, CalculeModelBoundingBox(CalculateBoundingBox(aux)), CalculeModelBoundingBox(correction),verticesBoundingBox);
    
        renderer->DrawMesh(vao, indices.size(), model, textures, shininess);
    
    }
}

BoundingBox Mesh::CalculateBoundingBox(const glm::mat4& parentModelMatrix)
{
    BoundingBox bbox;
    
    std::vector<Vertex> allVertices = AcumulativeVertex(parentModelMatrix,position);
    bbox.min = bbox.max = glm::vec3(parentModelMatrix* glm::vec4(vertices[0].position, 1.0f));
    
    for (int i = 0; i < vertices.size(); i++)
    {
        glm::vec4 worldPosition = parentModelMatrix * glm::vec4(vertices[i].position, 1.0f);
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
        BoundingBox childBox = child->CalculateBoundingBox(model);
    
        if (childBox.min.x < bbox.min.x) bbox.min.x = childBox.min.x;
        if (childBox.max.x > bbox.max.x) bbox.max.x = childBox.max.x;
        if (childBox.min.y < bbox.min.y) bbox.min.y = childBox.min.y;
        if (childBox.max.y > bbox.max.y) bbox.max.y = childBox.max.y;
        if (childBox.min.z < bbox.min.z) bbox.min.z = childBox.min.z;
        if (childBox.max.z > bbox.max.z) bbox.max.z = childBox.max.z;
    }

    //verticesBoundingBox[0] = glm::vec3(bbox.min.x, bbox.min.y, bbox.min.z);
    //verticesBoundingBox[1] = glm::vec3(bbox.max.x, bbox.min.y, bbox.min.z);
    //verticesBoundingBox[2] = glm::vec3(bbox.max.x, bbox.max.y, bbox.min.z);
    //verticesBoundingBox[3] = glm::vec3(bbox.min.x, bbox.max.y, bbox.min.z);
    //verticesBoundingBox[4] = glm::vec3(bbox.min.x, bbox.min.y, bbox.max.z);
    //verticesBoundingBox[5] = glm::vec3(bbox.max.x, bbox.min.y, bbox.max.z);
    //verticesBoundingBox[6] = glm::vec3(bbox.max.x, bbox.max.y, bbox.max.z);
    //verticesBoundingBox[7] = glm::vec3(bbox.min.x, bbox.max.y, bbox.max.z);

    // Compensa las coordenadas para volver a las locales
    //glm::vec4 localMin = glm::inverse(parentModelMatrix) * glm::vec4(bbox.min, 1.0f);
    //glm::vec4 localMax = glm::inverse(parentModelMatrix) * glm::vec4(bbox.max, 1.0f);
    //
    //bbox.min = glm::vec3(localMin);
    //bbox.max = glm::vec3(localMax);
    // 
    // 
    // 
    // 
    //BoundingBox bbox;
    //std::vector<Vertex> allVertices;
    //for (const auto& ver : vertices)
    //{
    //    Vertex aux = ver;
    //    allVertices.push_back(aux);
    //}
    //allVertices = AcumulativeVertex(model, position);
    //
    //bbox.min.x = bbox.max.x = allVertices[0].position.x;
    //bbox.min.y = bbox.max.y = allVertices[0].position.y;
    //bbox.min.z = bbox.max.z = allVertices[0].position.z;
    //
    //
    //for (int i = 0; i < allVertices.size(); i++)
    //{
    //    if (allVertices[i].position.x < bbox.min.x) bbox.min.x = allVertices[i].position.x;
    //    if (allVertices[i].position.x > bbox.min.x) bbox.max.x = allVertices[i].position.x;
    //    if (allVertices[i].position.y < bbox.min.y) bbox.min.y = allVertices[i].position.y;
    //    if (allVertices[i].position.y > bbox.max.y) bbox.max.y = allVertices[i].position.y;
    //    if (allVertices[i].position.z < bbox.min.z) bbox.min.z = allVertices[i].position.z;
    //    if (allVertices[i].position.z > bbox.max.z) bbox.max.z = allVertices[i].position.z;
    //}

    //std::cout << bbox.min.x << " " << bbox.max.x << " " << position.x << std::endl;
   

    return bbox;
}
std::vector<Vertex> Mesh::AcumulativeVertex(glm::mat4 parentModel,glm::vec3 parentPosition)
{

    std::vector<Vertex> allVertices;
    for (const auto& child : children)
    {
        allVertices = child->AcumulativeVertex(model,localPosition);

    }
    for (const auto& ver : vertices)
    {
        allVertices.push_back(ver);
    }

    return allVertices;
}

glm::mat4 Mesh::CalculeModelBoundingBox(BoundingBox bbox)
{
    glm::vec3 size = glm::vec3(bbox.max.x- bbox.min.x, bbox.max.y  - bbox.min.y , bbox.max.z - bbox.min.z );
    glm::vec3 center = glm::vec3((bbox.min.x + bbox.max.x) / 2, (bbox.min.y + bbox.max.y) / 2, (bbox.min.z + bbox.max.z) / 2);
    glm::mat4 transform = glm::translate(glm::mat4(1),center) * glm::scale(glm::mat4(1), size);

    glm::mat4 m = model;
    m = glm::scale(glm::mat4(1.0f), glm::vec3(1,1,1));
    return (model * transform);
    //return glm::mat4();
}

std::vector<glm::vec3> Mesh::GetTransformedVertices() const {
    std::vector<glm::vec3> transformedVertices;
    for (const auto& vertex : vertices) {
        // Aplica la transformación local a cada vértice
        glm::vec4 transformedVertex = model * glm::vec4(vertex.position, 1.0f);
        transformedVertices.push_back(glm::vec3(transformedVertex));
    }
    return transformedVertices;
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
        position =  localPosition;

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

void Mesh::InfoAboutCol(float ix, float ax, float iy, float ay, float iz, float az)
{
    correction.min.x = ix;
    correction.min.y = iy;
    correction.min.z = iz;

    correction.max.x = ax;
    correction.max.y = ay;
    correction.max.z = az;
    verticesBoundingBox[0] = glm::vec3(correction.min.x, correction.min.y, correction.min.z);
    verticesBoundingBox[1] = glm::vec3(correction.max.x, correction.min.y, correction.min.z);
    verticesBoundingBox[2] = glm::vec3(correction.max.x, correction.max.y, correction.min.z);
    verticesBoundingBox[3] = glm::vec3(correction.min.x, correction.max.y, correction.min.z);
    verticesBoundingBox[4] = glm::vec3(correction.min.x, correction.min.y, correction.max.z);
    verticesBoundingBox[5] = glm::vec3(correction.max.x, correction.min.y, correction.max.z);
    verticesBoundingBox[6] = glm::vec3(correction.max.x, correction.max.y, correction.max.z);
    verticesBoundingBox[7] = glm::vec3(correction.min.x, correction.max.y, correction.max.z);
}
