#include "BlockComponent.h"

std::unordered_map<BlockComponent::EColor, std::string> BlockComponent::ColorTextureSignatures_ = {
	{ BlockComponent::EColor::BLUE,   "Blue"   },
	{ BlockComponent::EColor::CYAN,   "Cyan"   },
	{ BlockComponent::EColor::GRAY,   "Gray"   },
	{ BlockComponent::EColor::GREEN,  "Green"  },
	{ BlockComponent::EColor::ORANGE, "Orange" },
	{ BlockComponent::EColor::PINK,   "Pink"   },
	{ BlockComponent::EColor::PURPLE, "Purple" },
	{ BlockComponent::EColor::RED,    "Red"    },
	{ BlockComponent::EColor::YELLOW, "Yellow" },
};

bool BlockComponent::IsCollision(const BlockComponent* BoundingBox)
{
	if (State_ == EState::EMPTY || BoundingBox->GetState() == EState::EMPTY)
	{
		return false;
	}

	return AABBComponent::IsCollision(BoundingBox);
}
