#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include "export/export.h"
#include "entity/Entity.h"
#include <list>
#include <vector>
class SlayerWxEngine_API DataManager
{
private:
	std::vector<Entity*> entities;
	Entity* selectedEntity;
	DataManager() { selectedEntity = nullptr;}
	static DataManager* _instance;
public:

	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;
	static DataManager* Get();
	~DataManager();
	void addEntity(Entity* entity, int id);
	void clearLevelEntities();
	std::vector<Entity*> getLevelEntities();
	Entity* getSelectedEntity();
	void setSelectedEntity(Entity* entity);
};
#endif