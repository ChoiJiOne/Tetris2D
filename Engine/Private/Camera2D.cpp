#include "Camera2D.h"

void Camera2D::Move(float DeltaSeconds)
{
	float CosTheta = cosf(Rotate_);
	float SinTheta = sinf(Rotate_);

	Position_.x += (CosTheta * GetVelocity() * DeltaSeconds);
	Position_.y += (SinTheta * GetVelocity() * DeltaSeconds);
}