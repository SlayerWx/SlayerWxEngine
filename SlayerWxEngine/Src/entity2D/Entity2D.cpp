#include "Entity2D.h"

Entity2D::Entity2D() : Entity()
{
	lastPosition = position;
}
#include <iostream>
bool Entity2D::CheckCollisionAABB(Entity2D& vs)
{
	if (canCollision &&  vs.canCollision)
	{
		if (position.x - (vs.localScale[0] / 2) < vs.position.x + (vs.localScale[0]/2) &&
			position.x + (localScale[0] / 2 ) > vs.position.x - (localScale[0] / 2) &&
			position.y - (vs.localScale[1] / 2) < vs.position.y + (vs.localScale[1]/2) &&
			position.y + (localScale[1]/2) > vs.position.y - (localScale[1] / 2))
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
				BackToLastPosition();
				
			}
			return true;
		}
	}
	return false;
}

float Entity2D::GetScaleX()
{
	return localScale.x;
}

float Entity2D::GetScaleY()
{
	return localScale.y;
}
void Entity2D::BackToLastPosition()
{
	position = lastPosition;
}
