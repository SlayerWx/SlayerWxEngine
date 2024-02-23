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

	for (int i = 0; i < _tileMapGrid.size(); i++) {
		for (int y = 0; y < _height; y++) {
			for (int x = 0; x < _width; x++) {
				if (_tileMapGrid[i][y][x].getId() != NULL) {
					_tileMapGrid[i][y][x].Draw();
					
				}
			}
		}
	}
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
			//newTile.Scale((_tileWidth / _imageWidth) * tilemapScale, (_tileHeight / _imageHeight) * tilemapScale, 0.1f);
			newTile.Scale(tilemapScale, tilemapScale, 0.1f);
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
		{
			tiles[id].walkability(false);
			tiles[id].canCollision = true;
		}
		else
		{
			tiles[id].walkability(true);
			tiles[id].canCollision = false;
		}

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


	for (int i = 0; i < _tileMapGrid.size(); i++) {
		for (int y = 0; y < _height; y++) {
			for (int x = 0; x < _width; x++) {
				if (_tileMapGrid[i][y][x].getId() != NULL) {
					_tileMapGrid[i][y][x].SetPosition(_tileMapGrid[i][y][x].GetScaleX() * x,
						_tileMapGrid[i][y][x].GetScaleY() * (_height - y)
						, i * 0.15f);

				}
			}
		}
	}


	return true;
}
//================================================
void Tilemap::checkCollision(Entity2D& object) {

	glm::vec2 playerPosition;
	playerPosition.x = object.GetPositionX(); // devuelve la posición del jugador en el mundo
	playerPosition.y = object.GetPositionY();

	// Convertir la posición relativa a coordenadas de celda
	convertedPosX = playerPosition.x / _tileMapGrid[0][0][0].GetScaleX();
	convertedPosY = _tileMapGrid[0][0][0].GetPositionY() / _tileMapGrid[0][0][0].GetScaleY() - playerPosition.y / _tileMapGrid[0][0][0].GetScaleY();

	int left_tile = convertedPosX;// std::round(convertedPosX);
	int right_tile = convertedPosX + (object.GetScaleX() / _tileMapGrid[0][0][0].GetScaleX());
	
	int top_tile = std::round(convertedPosY);
	int bottom_tile = convertedPosY + (object.GetScaleY() / _tileMapGrid[0][0][0].GetScaleY());


	//if (left_tile < 0.00f)
	//{
	//	left_tile = 0;
	//	object.BackToLastPosition();
	//}
	//
	//if (right_tile >= _width)
	//{
	//	right_tile = _width - 1;
	//
	//	object.BackToLastPosition();
	//}
	//
	//if (top_tile < 0.00f)
	//{
	//	top_tile = 0; 
	//	object.BackToLastPosition();
	//}
	//
	//if (bottom_tile >= _height)
	//{
	//	bottom_tile = _height - 1;
	//
	//	object.BackToLastPosition();
	//}
	std::cout << left_tile << "  " << std::round(convertedPosX) << "   " << convertedPosX << std::endl;
	for (int i = 0; i <= _width-1; i++) {
	//for (int i = left_tile; i <= right_tile; i++) {
	
		for (int j = top_tile; j <= bottom_tile; j++) {
	
			for (int k = 0; k < _tileMapGrid.size(); k++) {
				if (!_tileMapGrid[k][j][i].isWalkable()) {
	
					object.CheckCollisionAABB(_tileMapGrid[k][j][i]);
				}
				
			}
		}
	}
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
