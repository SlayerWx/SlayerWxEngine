#ifndef MATERIAL2D_H
#define MATERIAL2D_H
#include "entity2D/Entity2D.h"
#include "textureImporter/TextureImporter.h"
struct SlayerWxEngine_API Material
{
    glm::vec4 color;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};
class SlayerWxEngine_API Cube : public Entity
{
private:
    static const int vertexLength = 192;
    float vertexMaterial[vertexLength] = {
        // positions          // normal                // texture coords
         0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // top left 

         0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

         0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0,   0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0,   0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0,   1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0,   0.0f, 1.0f
    };
    static const int indexLength = 36;
    unsigned int index[indexLength] = {
        0, 1, 3, // first triangle
        1, 2, 3,  // second triangle
        4, 5, 7,
        5, 6, 7,
        8, 9, 11,
        9, 10, 11,
        12, 13, 15,
        13, 14, 15,
        16, 17, 19,
        17, 18, 19,
        20, 21, 23,
        21, 22, 23
    };
    TextureData data;
    bool alpha = false;

    Material material;
public:
    void SetTextureCoordinate(float u0, float v0, float u1, float v1,
        float u2, float v2, float u3, float v3);
    Cube();
    Cube(const char* filePath);
    void Draw();
};
#endif