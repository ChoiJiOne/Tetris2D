#include "AABBComponent.h"

bool AABBComponent::IsCollision(const AABBComponent* BoundingBox)
{
	Vec2f MinPosition = GetMinPosition();
	Vec2f MaxPosition = GetMaxPosition();

	Vec2f OtherMinPosition = BoundingBox->GetMinPosition();
	Vec2f OtherMaxPosition = BoundingBox->GetMaxPosition();

	if (MaxPosition.x <= OtherMinPosition.x || MinPosition.x >= OtherMaxPosition.x)
	{
		return false;
	}

	if (MaxPosition.y <= OtherMinPosition.y || MinPosition.y >= OtherMaxPosition.y)
	{
		return false;
	}

	return true;
}