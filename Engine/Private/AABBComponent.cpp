#include "AABBComponent.h"

bool AABBComponent::IsCollision(const AABBComponent* BoundingBox)
{
	Vec2f MinPosition = GetMinPosition();
	Vec2f MaxPosition = GetMaxPosition();

	Vec2f OtherMinPosition = BoundingBox->GetMinPosition();
	Vec2f OtherMaxPosition = BoundingBox->GetMaxPosition();

	return (MaxPosition.x <= OtherMinPosition.x || MinPosition.x >= OtherMaxPosition.x)
		&& (MaxPosition.y <= OtherMinPosition.y || MinPosition.y >= OtherMaxPosition.y);
}