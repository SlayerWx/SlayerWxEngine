#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "tinyxml2.h"
#include <vector>
#include <string>

class SlayerWxEngine_API Tilemap {
public:
    Tilemap(const char* tmxFilePath, const char* imageFilePath);
    ~Tilemap();

    void LoadMap(const char* tmxFilePath, const char* imageFilePath);
    void Draw(); // Puedes implementar esta función para renderizar el mapa

    void CheckCollisionWithTileMap(Entity2D* player, glm::vec3 actualPosition, float speed);

    void SetDimensions(/*float width, float height*/);

private:
    std::vector<Tile> tiles;
    std::vector<Tile**> grid;
    unsigned int gridWidth;
    unsigned int gridHeight;
    float tileWidth;  
    float tileHeight;
    float imageWidth;
    float imageHeight;
    int columns = 0;
    int rows = 0;
    int tilesAmmount = 0;
    std::string imagePath;
    TextureData imageTexture;

    const Tile& GetTileFromID(unsigned int uiId);
    //void SetDimensions(float width, float height);
    //const Tile& GetTileForIndex(unsigned int uiId);
    ///void checkCollision(Entity2D& object);
    //Tile* FindTileAtTextureCoordinate(float textureX, float textureY);
    //void SetAdyacentTiles();
    void SetPropertiesPath(const char* path, Tile* myTile);
};

#endif