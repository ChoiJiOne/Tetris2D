#include "TetrominoInputComponent.h"
#include "BlockComponent.h"
#include "InputManager.h"
#include "Tetromino.h"

static const std::unordered_map<EKeyCode, Tetromino::EDirection> KEY_DIRECTIONS = {
	{ EKeyCode::CODE_LEFT,  Tetromino::EDirection::LEFT  },
	{ EKeyCode::CODE_RIGHT, Tetromino::EDirection::RIGHT },
	{ EKeyCode::CODE_UP,    Tetromino::EDirection::CW    },
	{ EKeyCode::CODE_DOWN,  Tetromino::EDirection::DOWN  },
};

void TetrominoInputComponent::Tick(float DeltaSecons)
{
	AccrueFrameTime_ += DeltaSecons;

	Tetromino::EDirection Direction = Tetromino::EDirection::NONE;
	
	for (const auto& KeyDirection : KEY_DIRECTIONS)
	{
		if (InputManager::Get().GetKeyPressState(KeyDirection.first) == EPressState::PRESSED)
		{
			Direction = KeyDirection.second;
		}
	}

	reinterpret_cast<Tetromino*>(GetGameObject())->Move(Direction);
}