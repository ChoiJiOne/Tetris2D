#include "TetrominoInputComponent.h"
#include "BlockComponent.h"
#include "InputManager.h"

static const std::unordered_map<EKeyCode, Tetromino::EDirection> KEY_DIRECTIONS = {
	{ EKeyCode::CODE_LEFT,   Tetromino::EDirection::LEFT  },
	{ EKeyCode::CODE_RIGHT,  Tetromino::EDirection::RIGHT },
	{ EKeyCode::CODE_UP,     Tetromino::EDirection::CW    },
	{ EKeyCode::CODE_DOWN,   Tetromino::EDirection::DOWN  },
	{ EKeyCode::CODE_SPACE,  Tetromino::EDirection::JUMP  },
};

void TetrominoInputComponent::Tick(float DeltaSecons)
{
	AccrueFrameTime_ += DeltaSecons;

	Direction_ = Tetromino::EDirection::NONE;

	for (const auto& KeyDirection : KEY_DIRECTIONS)
	{
		if (InputManager::Get().GetKeyPressState(KeyDirection.first) == EPressState::PRESSED)
		{
			Direction_ = KeyDirection.second;
		}
	}
}