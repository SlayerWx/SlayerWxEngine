#ifndef ENTITY_H
#define ENTITY_H
#include "export/export.h"
#include "renderer/renderer.h"

class SlayerWxEngine_API Entity
{
public:
	Renderer* renderer;
	Entity();
	Entity(Renderer* renderer);
};

#endif // !ENTITY_H
