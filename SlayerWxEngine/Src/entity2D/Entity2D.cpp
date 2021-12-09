#include "Entity2D.h"

Entity2D::Entity2D() : Entity()
{
}
#include <iostream>
bool Entity2D::CheckCollisionAABB(Entity2D& vs)
{
	if (canCollision &&  vs.canCollision)
	{
		if (position.x < vs.position.x + vs.localScale[0] &&
			position.x + localScale[0] > vs.position.x &&
			position.y < vs.position.y + vs.localScale[1] &&
			position.y + localScale[1] > vs.position.y)
		{
			if (vs.weight < strength)
			{
				bool helpWeight = false;
				if (vs.weight == 0)
				{
					helpWeight = true;
					vs.weight = 0.00001;
				}
				vs.SetPosition(vs.GetPositionX() + (position.x - lastPosition.x),
								vs.GetPositionY() + (position.y - lastPosition.y),
								vs.GetPositionZ());
				if (helpWeight)
				{
					vs.weight = 0.0f;
				}
			}
			else
			{

				position = lastPosition;
			}
			return true;
		}
	}
	return false;
}
