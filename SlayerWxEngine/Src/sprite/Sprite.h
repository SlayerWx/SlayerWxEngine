#ifndef SPRITE_H
#define SPRITE_H
#include "entity2D/Entity2D.h"
#include "textureImporter/TextureImporter.h"
class SlayerWxEngine_API Sprite : public Entity2D
{
private:
    static const int vertexLength = 36;
    float vertexSprite[vertexLength] = {
        // positions          // colors                // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f,   0.0f, 1.0f  // top left 
    };
    static const int indexLength = 6;
    unsigned int index[indexLength] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    TextureData data;
    bool alpha = false;
public:

    Sprite();
    Sprite(const char* filePath);
    void Draw();
};
#endif