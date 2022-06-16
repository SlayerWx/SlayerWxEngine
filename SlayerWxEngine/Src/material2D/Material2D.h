#ifndef MATERIAL2D_H
#define MATERIAL2D_H
#include "entity2D/Entity2D.h"
#include "textureImporter/TextureImporter.h"
class SlayerWxEngine_API Material2D : public Entity2D
{
private:
    static const int vertexLength = 36;
    float vertexMaterial[vertexLength] = {
        // positions          // normal                // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
    };
    static const int indexLength = 6;
    unsigned int index[indexLength] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    TextureData data;
    bool alpha = false;
public:
    void SetTextureCoordinate(float u0, float v0, float u1, float v1,
        float u2, float v2, float u3, float v3);
    Material2D();
    Material2D(const char* filePath);
    void Draw();
};
#endif