#include "BlockComponent.h"

std::unordered_map<BlockComponent::EType, std::string> BlockComponent::TypeTextureSignatures_ = {
	{ BlockComponent::EType::BLUE,   "Blue"   },
	{ BlockComponent::EType::CYAN,   "Cyan"   },
	{ BlockComponent::EType::GRAY,   "Gray"   },
	{ BlockComponent::EType::GREEN,  "Green"  },
	{ BlockComponent::EType::ORANGE, "Orange" },
	{ BlockComponent::EType::PINK,   "Pink"   },
	{ BlockComponent::EType::PURPLE, "Purple" },
	{ BlockComponent::EType::RED,    "Red"    },
	{ BlockComponent::EType::YELLOW, "Yellow" },
};