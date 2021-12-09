#ifndef ENTITY2D_H
#define ENTITY2D_H
#include "export/export.h"
#include "entity/Entity.h"

class SlayerWxEngine_API Entity2D : public Entity
{
public:
	Entity2D();
	bool canCollision = false;
	bool CheckCollisionAABB(Entity2D vs);
	
};

#endif
