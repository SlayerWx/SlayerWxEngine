#include "Tilemap.h"
#include <iostream>
#include <sstream>


Tilemap::Tilemap() {}
Tilemap::~Tilemap() {}
const Tile& Tilemap::tile(unsigned int uiId) {
	Tile* NoTile = nullptr;

	for (int i = 0; i < tiles.size(); i++) {
		if (uiId == tiles[i].getId()) {
			return tiles[i];
		}
	}

	return *NoTile;
}
//================================================
void Tilemap::setMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId) {
	_tileMapGrid[layer][uiCol][uiRow] = tile(uiId);
}
//================================================
void Tilemap::setTile(const Tile& rkTile) {
	tiles.push_back(rkTile);
}
//================================================
void Tilemap::setTileDimensions(float tileWidth, float tileHeight) {
	_tileWidth = tileWidth;
	_tileHeight = tileHeight;
}
//================================================
void Tilemap::setDimensions(float width, float height) {
	_width = width;
	_height = height;

	//creo la grilla bidimensional para guardar la posicion de cada tile igual que en el editor
	Tile** tileMap;
	tileMap = new Tile * [_height];
	for (int i = 0; i < _height; i++) {
		tileMap[i] = new Tile[_width];
	}
	_tileMapGrid.push_back(tileMap);
}
//================================================
void Tilemap::setTexture(const TextureData& rkTexture) {
	_texture = rkTexture;
}
//================================================
void Tilemap::draw() {

	float mapWidth = -(_width * _tileWidth) / 2;
	float mapHeight = (_height * _tileHeight) / 2;

	for (int i = 0; i < _tileMapGrid.size(); i++) {
		for (int y = 0; y < _height; y++) {
			for (int x = 0; x < _width; x++) {
				if (_tileMapGrid[i][y][x].getId() != NULL) {
					_tileMapGrid[i][y][x].SetPosition(x, _height -y, i * 0.15f);

					_tileMapGrid[i][y][x].Draw();
				}
			}
		}
	}
	return;
}
//================================================
bool Tilemap::importTileMap(std::string filePath) {
	tinyxml2::XMLDocument doc; //guarda el documento
	tinyxml2::XMLError errorHandler; //guarda el resultado de las funciones

	errorHandler = doc.LoadFile(filePath.c_str()); //carga el archivo XML
	if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) return false;

	// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
	tinyxml2::XMLElement* mapNode = doc.FirstChildElement("map");
	if (mapNode == nullptr)
		return false;
	setDimensions(mapNode->FloatAttribute("width"), mapNode->FloatAttribute("height"));				// Get width and heigth for
	setTileDimensions(mapNode->FloatAttribute("tilewidth"), mapNode->FloatAttribute("tileheight")); // the map and the tiles

	// Loading Tilset element
	tinyxml2::XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset == NULL)
		return false;

	int tileCount = pTileset->IntAttribute("tilecount"); // Number of Tiles in the Tileset
	int columns = pTileset->IntAttribute("columns");  // Columns of Tiles in the Tileset
	int rows = tileCount / columns;
	float spacing = pTileset->IntAttribute("spacing");
	_imagePath = "Assets/";																//
	_imagePath += pTileset->FirstChildElement("image")->Attribute("source");			// Loading Textures
	setTexture(TextureImporter::ImportTexture(_imagePath.c_str())); 

	// Save the Tiles in the TileMap
	_imageWidth = pTileset->FirstChildElement("image")->IntAttribute("width");
	_imageHeight = pTileset->FirstChildElement("image")->IntAttribute("height");
	float tileX = 0.0f, tileY = 0.0f;
	int _id = 1;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Tile newTile;

			newTile.setId(_id);
			newTile.SetDataTexture(_texture);
			//newTile.Scale(_tileWidth, _tileHeight,0.1f);

			//newTile.SetTextureCoordinate(tileX / _imageWidth, tileY / _imageHeight,
			//	(tileX + _tileWidth) / _imageWidth, tileY / _imageHeight,
			//	tileX / _imageWidth, (tileY + _tileHeight) / _imageHeight,
			//	(tileX + _tileWidth) / _imageWidth, (tileY + _tileHeight) / _imageHeight);

			int m = j;
			int n = rows -i -1;
			float tileXX = (_tileWidth / _imageWidth);
			float tileYY = (_tileHeight / _imageHeight);                        
			float left = m * (tileXX + (spacing/ _imageWidth));
			float right = left + tileXX;
			float down = n * (tileYY + (spacing / _imageHeight));
			float up =    down + tileYY;
			newTile.SetTextureCoordinate(left,down,right,down,left,up,right,up);

			tileX += _tileWidth;
			setTile(newTile);
			_id++;
		}
		tileX = 0;
		tileY += _tileHeight;
	}

	tinyxml2::XMLElement* pTile = pTileset->FirstChildElement("tile");

	while (pTile) {
		unsigned int id = pTile->IntAttribute("id");
		tinyxml2::XMLElement* pProperty = pTile->FirstChildElement("properties")->FirstChildElement("property");
		std::string propertyName = pProperty->Attribute("value");
		if (propertyName == "false")
			tiles[id].walkability(false);
		else
			tiles[id].walkability(true);

		pTile = pTile->NextSiblingElement("tile");
	}

	// Loading Layer element
	tinyxml2::XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer == NULL)
		return false;

	int layerCount = 0;
	while (pLayer) {
		// Loading Data element
		tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
		if (pData == NULL)
			return false;

		if (layerCount > 0) {
			Tile** tileMap;
			tileMap = new Tile * [_height];
			for (int i = 0; i < _height; i++) {
				tileMap[i] = new Tile[_width];
			}
			_tileMapGrid.push_back(tileMap);
		}

		while (pData) {
			std::vector<int> tileGids;

			const char* csvData = pData->GetText();
			if (csvData) {
				std::istringstream ss(csvData);
				std::string token;

				int col = 0;

				while (std::getline(ss, token, ',')) {
					int tileId = std::stoi(token);
					tileGids.push_back(tileId);
				}
			}


			int gid = 0;
			for (int y = 0; y < _height; y++) {
				for (int x = 0; x < _width; x++) {
					if (tileGids[gid] != 0)
						setMapTileId(layerCount, y, x, tileGids[gid]);
					gid++;
				}
			}

			pData = pData->NextSiblingElement("data");
		}
		layerCount++;
		pLayer = pLayer->NextSiblingElement("layer");
	}

	return true;
}
//================================================
void Tilemap::checkCollision(Entity2D& object) {

	//convertedPosX = object.posX() + (_width / 2) * _tileWidth;
	//convertedPosY = object.posY() - (_height / 2) * _tileHeight;
	//
	//int left_tile = convertedPosX / _tileWidth;
	//int right_tile = (convertedPosX + object.scaleX()) / _tileWidth;
	//
	//int top_tile = (convertedPosY / _tileHeight) * -1;
	//int bottom_tile = ((convertedPosY - object.scaleY()) / _tileHeight) * -1; // Se resta porque el eje Y crece hacia arriba
	//
	//if (left_tile < 0)
	//	left_tile = 0;
	//
	//if (right_tile >= _width)
	//	right_tile = _width - 1;
	//
	//if (top_tile < 0)
	//	top_tile = 0;
	//
	//if (bottom_tile >= _height)
	//	bottom_tile = _height - 1;
	//
	///*
	//cout << "converted X: " << convertedPosX << endl;
	//cout << "converted Y: " << convertedPosY << endl;
	//
	//cout << "left: " <<left_tile << endl;
	//cout << "right: "<<right_tile << endl;
	//cout << "top: " << top_tile << endl;
	//cout << "bottom: "<<bottom_tile << endl;
	//*/
	//
	//for (int i = left_tile; i <= right_tile; i++) {
	//
	//	for (int j = top_tile; j <= bottom_tile; j++) {
	//
	//		for (int k = 0; k < _tileMapGrid.size(); k++) {
	//			//cout << "caminable " << "[" << k << "]" << "[" << j << "]" << "[" << i << "] : "<< _tileMapGrid[k][j][i].isWalkable() << endl; // true == 1  ; false == 0
	//			//cout << true << endl;
	//			if (!_tileMapGrid[k][j][i].isWalkable()) {
	//
	//				if (_tileMapGrid[k][j][i].checkCollision(object) == CollisionHorizontalRight ||
	//					_tileMapGrid[k][j][i].checkCollision(object) == CollisionHorizontalLeft)
	//					object.returnToPreviusPosH();
	//
	//				if (_tileMapGrid[k][j][i].checkCollision(object) == CollisionVerticalUp)
	//					object.returnToPreviusPos(object.posX(), object.previusPosY() + 0.2);
	//
	//				else if (_tileMapGrid[k][j][i].checkCollision(object) == CollisionVerticalDown)
	//					object.returnToPreviusPos(object.posX(), object.previusPosY() - 0.2);
	//			}
	//		}
	//	}
	//}
}





//Tilemap::Tilemap() : mapWidth(0), mapHeight(0), tileWidth(0), tileHeight(0) {}
//
//Tilemap::~Tilemap() {
//    // Liberar la memoria de los tiles
//    for (auto& row : grid) {
//        for (auto tile : row) {
//            delete tile;
//        }
//    }
//}
//
//void Tilemap::LoadMap(const char* tmxFilePath) {
//	tinyxml2::XMLDocument doc; //guarda el documento
//	tinyxml2::XMLError errorHandler; //guarda el resultado de las funciones
//
//	errorHandler = doc.LoadFile(tmxFilePath); //carga el archivo XML
//	if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) return;
//
//	// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
//	tinyxml2::XMLElement* mapNode = doc.FirstChildElement("map");
//	if (mapNode == nullptr) return;
//
//	mapNode->FloatAttribute("width");
//	mapNode->FloatAttribute("height");
//	
//}
//
//
//











//
//void Tilemap::LoadMap(const char* tmxFilePath) {
//    tinyxml2::XMLDocument doc;
//    doc.LoadFile(tmxFilePath);
//
//    // Obtener información del mapa
//    tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");
//    mapElement->QueryIntAttribute("width", &width);
//    mapElement->QueryIntAttribute("height", &height);
//
//    // Inicializar la matriz de tiles
//    tileMap.resize(height, std::vector<Tile>(width));
//
//    // Iterar sobre las capas y cargar los tiles
//    tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
//    int layerIndex = 0;
//
//    while (layerElement) {
//        tinyxml2::XMLElement* dataElement = layerElement->FirstChildElement("data");
//
//        if (dataElement) {
//            const char* tileData = dataElement->GetText();
//
//            if (tileData) {
//                // Procesar los datos y cargar en la matriz tileMap
//                // (Necesitarás adaptar esta parte según el formato real de tus datos en el archivo TMX)
//                // Ejemplo básico: Asignar el mismo tile para cada posición
//                for (int y = 0; y < height; ++y) {
//                    for (int x = 0; x < width; ++x) {
//                        int tileId = 0; // Obtén el ID del tile según tus datos reales
//                        tileMap[y][x] = Tile(tileId);
//                    }
//                }
//            }
//        }
//
//        layerElement = layerElement->NextSiblingElement("layer");
//        layerIndex++;
//    }
//}
//


























//Tilemap::Tilemap(const char* tmxFilePath, const char* imageFilePath) {
//	columns = 0;
//	rows = 0;
//
//    LoadMap(tmxFilePath, imageFilePath);
//}
//
//Tilemap::~Tilemap() {
//    // Aquí puedes liberar recursos si es necesario.
//}
//
//void Tilemap::LoadMap(const char* tmxFilePath, const char* imageFilePath) {
//	tinyxml2::XMLDocument doc;
//    doc.LoadFile(tmxFilePath);
//
//    // Obtener información del mapa
//    tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");
//    mapElement->QueryIntAttribute("width", &width);
//    mapElement->QueryIntAttribute("height", &height);
//
//    // Inicializar la matriz de tiles
//    tileMap.resize(height, std::vector<Tile>(width));
//
//    // Iterar sobre las capas y cargar los tiles
//    tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
//    int layerIndex = 0;
//
//    while (layerElement) {
//        tinyxml2::XMLElement* dataElement = layerElement->FirstChildElement("data");
//
//        if (dataElement) {
//            const char* tileData = dataElement->GetText();
//
//            if (tileData) {
//                // Procesar los datos y cargar en la matriz tileMap
//                // (Necesitarás adaptar esta parte según el formato real de tus datos en el archivo TMX)
//                // Ejemplo básico: Asignar el mismo tile para cada posición
//                for (int y = 0; y < height; ++y) {
//                    for (int x = 0; x < width; ++x) {
//                        int tileId = 0; // Obtén el ID del tile según tus datos reales
//                        tileMap[y][x] = Tile(tileId);
//                    }
//                }
//            }
//        }
//
//        layerElement = layerElement->NextSiblingElement("layer");
//        layerIndex++;
//    }
//}
//
//void Tilemap::SetPropertiesPath(const char* path,Tile* myTile)
//{
//	tinyxml2::XMLDocument map;
//	map.LoadFile(path);
//
//	tinyxml2::XMLElement* Tileset = map.FirstChildElement("tileset");
//	if (Tileset) {
//		for (tinyxml2::XMLNode* tile = Tileset->FirstChildElement(); tile; tile = tile->NextSiblingElement()) {
//			if (tile->ToElement() && tile->ToElement()->IntAttribute("id") && tile->ToElement()->IntAttribute("id") == myTile->GetId()) {
//				const char* name = "";
//				tinyxml2::XMLElement* properties = tile->FirstChildElement("properties");
//				if (properties) {
//					tinyxml2::XMLElement* value = properties->FirstChildElement("property");
//					if (value) {
//						myTile->SetWalkeable(value->BoolAttribute("value"));
//
//					}
//				}
//			}
//		}
//	}
//	map.Clear();
//}
//
//
//
////void Tilemap::SetAdyacentTiles()
////{
////	for (int i = 0; i < tiles.size(); i++) {
////		for (int j = 0; j < tiles[i].size(); j++) {
////			for (int k = 0; k < tiles[i][j].size(); k++) {
////				if (tiles[i][j][k]) {
////					if ((k - 1) >= 0 && tiles[i][j][k - 1])tiles[i][j][k]->SetLeft(tiles[i][j][k - 1]);
////
////					if ((j - 1) >= 0 && tiles[i][j - 1][k])tiles[i][j][k]->SetTop(tiles[i][j - 1][k]);
////
////					if ((k + 1 < tiles[i][j].size()) && tiles[i][j][k + 1])tiles[i][j][k]->SetRight(tiles[i][j][k + 1]);
////
////					if ((j + 1 < tiles[i][j].size()) && tiles[i][j + 1][k])tiles[i][j][k]->SetBottom(tiles[i][j + 1][k]);
////				}
////			}
////		}
////	}
////}
//
//void Tilemap::Draw() {
//
//	for (int i = 0; i < grid.size(); i++) {
//		for (int y = 0; y < rows; y++) {
//			for (int x = 0; x < columns; x++) {
//				if (grid[i][y][x].GetId() != NULL) {
//					grid[i][y][x].SetPosition(/*mapWidth + (tileWidth */ x, /*(mapHeight - (tileHeight */ y/*)*/, i * 0.1);
//					grid[i][y][x].Draw();
//				}
//			}
//		}
//	}
//
//}
//
//void Tilemap::CheckCollisionWithTileMap(Entity2D* player, glm::vec3 actualPosition, float speed) {
////
////
////
////	/*for (int i = 0; i < tiles.size(); i++) {
////
////		if (tiles[i] && !tiles[i]->GetIsWalkable()) {
////			collisionManager->CheckCollision(player, tiles[i], speed);
////		}
////	}*/
////	for (int i = 0; i < tiles.size(); i++) {
////		for (int j = 0; j < tiles[i].size(); j++) {
////			for (int k = 0; k < tiles[i][j].size(); k++) {
////				if (tiles[i][j][k] && currentTile != tiles[i][j][k] && collisionManager->CheckTrigger(player, tiles[i][j][k])) {
////					currentTile = tiles[i][j][k];
////				}
////			}
////		}
////	}
////	if (currentTile != nullptr && currentTile->GetIsWalkable()) {
////		for (Tile* tile : currentTile->GetAdyacentTiles()) {
////			if (tile && !tile->GetIsWalkable()) {
////				collisionManager->CheckCollision(player, tile, speed);
////			}
////		}
////	}
////	else {
////		if (currentTile)
////			collisionManager->CheckCollision(player, currentTile, speed);
////	}
//}
//void Tilemap::SetDimensions(/*float width, float height*/) {
//	//gridWidth = width;
//	//gridHeight = height;
//
//	//creo la grilla bidimensional para guardar la posicion de cada tile igual que en el editor
//	Tile** tileMap;
//	tileMap = new Tile * [rows];
//	for (int i = 0; i < rows; i++) {
//		tileMap[i] = new Tile[columns];
//	}
//	grid.push_back(tileMap);
//}
//
//
//const Tile& Tilemap::GetTileFromID(unsigned int uiId) {
//	Tile* NoTile = nullptr;
//	if(uiId < 458)
//	if (tiles[uiId].GetId() != NULL)
//	{
//		return tiles[uiId];
//	}
//	//for (int i = 0; i < tiles.size(); i++) {
//	//	if (uiId == tiles[i].GetId()) {
//	//		return tiles[i];
//	//	}
//	//}
//
//	return *NoTile;
//}
//
