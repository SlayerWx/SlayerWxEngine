#include "DataManager.h"
#include <iostream>
#include <mutex>

DataManager* DataManager::_instance = nullptr;

DataManager* DataManager::Get() {
	if (_instance == NULL) {
		_instance = new DataManager();
		//entities = new std::vector<Entity*>();
	}
	return _instance;
}

DataManager::~DataManager() {
	if (!entities.empty()) {
		entities.clear();
	}
}

void DataManager::addEntity(Entity* entity, int id) {
	if (entity != NULL) 
	{
		entity->id = id;
		entities.push_back(entity);
	}
}

void DataManager::clearLevelEntities() {
	entities.clear();
}

std::vector<Entity*> DataManager::getLevelEntities() {
	return entities;
}

void DataManager::setSelectedEntity(Entity* entity) {
	selectedEntity = entity;
}

Entity* DataManager::getSelectedEntity() {
	return selectedEntity;
}