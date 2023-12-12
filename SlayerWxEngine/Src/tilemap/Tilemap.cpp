#include "Tilemap.h"
#include <iostream>
#include <sstream>
Tilemap::Tilemap(const char* tmxFilePath, const char* imageFilePath) {
	columns = 0;
	rows = 0;

    LoadMap(tmxFilePath, imageFilePath);
}

Tilemap::~Tilemap() {
    // Aquí puedes liberar recursos si es necesario.
}

void Tilemap::LoadMap(const char* tmxFilePath, const char* imageFilePath) {
	tinyxml2::XMLDocument doc; //guarda el documento
	tinyxml2::XMLError errorHandler; //guarda el resultado de las funciones

	errorHandler = doc.LoadFile(tmxFilePath); //carga el archivo XML
	if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) return;

	// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
	tinyxml2::XMLElement* mapNode = doc.FirstChildElement("map");
	if (mapNode == nullptr)
		return;
	//SetDimensions(mapNode->FloatAttribute("width"), mapNode->FloatAttribute("height"));				// Get width and heigth for
	tileWidth = mapNode->FloatAttribute("tilewidth");
	tileHeight = mapNode->FloatAttribute("tileheight"); // the map and the tiles

	// Loading Tilset element
	tinyxml2::XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset == NULL)
		return;

	int tileCount = pTileset->IntAttribute("tilecount"); // Number of Tiles in the Tileset
	columns = pTileset->IntAttribute("columns");  // Columns of Tiles in the Tileset
	rows = tileCount / columns;
	SetDimensions();
	imagePath = "Assets/";																//
	imagePath += pTileset->FirstChildElement("image")->Attribute("source");			// Loading Textures
	imageTexture = TextureImporter::ImportTexture(imagePath.c_str()); //

	// Save the Tiles in the TileMap
	imageWidth = pTileset->FirstChildElement("image")->IntAttribute("width");
	imageHeight = pTileset->FirstChildElement("image")->IntAttribute("height");

	//CARGA DE TILE X TILE del atlas

	float _tileX = 0;
	float _tileY = 0;
	int _tileCountAux = 0;
	for (int i = 1; i < rows; i++)
	{
		for (int t = 0; t < columns; t++)
		{
			Tile newTile;
			newTile.SetId(_tileCountAux);
			newTile.SetDataTexture(imageTexture);

			_tileX = (t * tileWidth);
			_tileY =  imageHeight - (i * tileHeight);// , imageHeight);
			newTile.SetTextureCoordinate(_tileX / imageWidth, _tileY / imageHeight,
				(_tileX + tileWidth) / imageWidth, _tileY / imageHeight,
				_tileX / imageWidth, (_tileY + tileHeight) / imageHeight,
				(_tileX + tileWidth) / imageWidth, (_tileY + tileHeight) / imageHeight);


			tiles.push_back(newTile);
			_tileCountAux++;
		}
	}





	///////////////////////////////////////////////// CARGA TILE X TILE TERMINADA

	tinyxml2::XMLElement* pTile = pTileset->FirstChildElement("tile");

	while (pTile) {
		unsigned int id = pTile->IntAttribute("id");
		tinyxml2::XMLElement* pProperty = pTile->FirstChildElement("properties")->FirstChildElement("property");
		std::string propertyName = pProperty->Attribute("value");
		if (propertyName == "false")
			tiles[id].SetWalkeable(false);
		else
			tiles[id].SetWalkeable(true);

		pTile = pTile->NextSiblingElement("tile");
	}

	// Loading Layer element
	tinyxml2::XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer == NULL)
		return;

	int layerCount = 0;
	while (pLayer) {
		// Loading Data element
		tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
		if (pData == NULL)
			return;

		if (layerCount > 0) {
			Tile** tileMap;
			tileMap = new Tile * [rows];
			for (int i = 0; i < rows; i++) {
				tileMap[i] = new Tile[columns];
			}
			grid.push_back(tileMap);
		}

		while (pData) {
			std::vector<int> tileGids;

			if (pData) {
				const char* tileData = pData->GetText();
				if (tileData) {
					std::istringstream ss(tileData);
					std::string token;

					// Tokenizar la cadena de IDs y convertir a enteros

					while (std::getline(ss, token, ',')) {
						tileGids.push_back(std::stoi(token));
					}

				}



			}
			int gridAuxY = 0;
			int gridAuxX = 0;
			for (int i = 0; i < tileGids.size(); i++)
			{
				grid[layerCount][gridAuxY][gridAuxX] = GetTileFromID(/*tileGids[i]*/ 547);
				gridAuxX++;
				if (gridAuxX >= columns)
				{
					gridAuxX = 0;
					gridAuxY++;
				}
			}



			pData = pData->NextSiblingElement("data");
		}
		layerCount++;
		pLayer = pLayer->NextSiblingElement("layer");
	}

	return;
}

void Tilemap::SetPropertiesPath(const char* path,Tile* myTile)
{
	tinyxml2::XMLDocument map;
	map.LoadFile(path);

	tinyxml2::XMLElement* Tileset = map.FirstChildElement("tileset");
	if (Tileset) {
		for (tinyxml2::XMLNode* tile = Tileset->FirstChildElement(); tile; tile = tile->NextSiblingElement()) {
			if (tile->ToElement() && tile->ToElement()->IntAttribute("id") && tile->ToElement()->IntAttribute("id") == myTile->GetId()) {
				const char* name = "";
				tinyxml2::XMLElement* properties = tile->FirstChildElement("properties");
				if (properties) {
					tinyxml2::XMLElement* value = properties->FirstChildElement("property");
					if (value) {
						myTile->SetWalkeable(value->BoolAttribute("value"));

					}
				}
			}
		}
	}
	map.Clear();
}



//void Tilemap::SetAdyacentTiles()
//{
//	for (int i = 0; i < tiles.size(); i++) {
//		for (int j = 0; j < tiles[i].size(); j++) {
//			for (int k = 0; k < tiles[i][j].size(); k++) {
//				if (tiles[i][j][k]) {
//					if ((k - 1) >= 0 && tiles[i][j][k - 1])tiles[i][j][k]->SetLeft(tiles[i][j][k - 1]);
//
//					if ((j - 1) >= 0 && tiles[i][j - 1][k])tiles[i][j][k]->SetTop(tiles[i][j - 1][k]);
//
//					if ((k + 1 < tiles[i][j].size()) && tiles[i][j][k + 1])tiles[i][j][k]->SetRight(tiles[i][j][k + 1]);
//
//					if ((j + 1 < tiles[i][j].size()) && tiles[i][j + 1][k])tiles[i][j][k]->SetBottom(tiles[i][j + 1][k]);
//				}
//			}
//		}
//	}
//}

void Tilemap::Draw() {

	for (int i = 0; i < grid.size(); i++) {
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < columns; x++) {
				if (grid[i][y][x].GetId() != NULL) {
					grid[i][y][x].SetPosition(/*mapWidth + (tileWidth */ x, /*(mapHeight - (tileHeight */ y/*)*/, i * 0.1);
					grid[i][y][x].Draw();
				}
			}
		}
	}

}

void Tilemap::CheckCollisionWithTileMap(Entity2D* player, glm::vec3 actualPosition, float speed) {
//
//
//
//	/*for (int i = 0; i < tiles.size(); i++) {
//
//		if (tiles[i] && !tiles[i]->GetIsWalkable()) {
//			collisionManager->CheckCollision(player, tiles[i], speed);
//		}
//	}*/
//	for (int i = 0; i < tiles.size(); i++) {
//		for (int j = 0; j < tiles[i].size(); j++) {
//			for (int k = 0; k < tiles[i][j].size(); k++) {
//				if (tiles[i][j][k] && currentTile != tiles[i][j][k] && collisionManager->CheckTrigger(player, tiles[i][j][k])) {
//					currentTile = tiles[i][j][k];
//				}
//			}
//		}
//	}
//	if (currentTile != nullptr && currentTile->GetIsWalkable()) {
//		for (Tile* tile : currentTile->GetAdyacentTiles()) {
//			if (tile && !tile->GetIsWalkable()) {
//				collisionManager->CheckCollision(player, tile, speed);
//			}
//		}
//	}
//	else {
//		if (currentTile)
//			collisionManager->CheckCollision(player, currentTile, speed);
//	}
}
void Tilemap::SetDimensions(/*float width, float height*/) {
	//gridWidth = width;
	//gridHeight = height;

	//creo la grilla bidimensional para guardar la posicion de cada tile igual que en el editor
	Tile** tileMap;
	tileMap = new Tile * [rows];
	for (int i = 0; i < rows; i++) {
		tileMap[i] = new Tile[columns];
	}
	grid.push_back(tileMap);
}


const Tile& Tilemap::GetTileFromID(unsigned int uiId) {
	Tile* NoTile = nullptr;

	if (tiles[uiId].GetId() != NULL)
	{
		return tiles[uiId];
	}
	//for (int i = 0; i < tiles.size(); i++) {
	//	if (uiId == tiles[i].GetId()) {
	//		return tiles[i];
	//	}
	//}

	return *NoTile;
}
