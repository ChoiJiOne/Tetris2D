#include "InputHelper.h"

Game::KeyboardState::KeyboardState()
	: CurrKeyboardState(SDL_Scancode::SDL_NUM_SCANCODES, 0)
	, PrevKeyboardState(SDL_Scancode::SDL_NUM_SCANCODES, 0)
{
}

Game::KeyboardState::~KeyboardState()
{
}

void Game::KeyboardState::Update()
{
	const uint8_t* KeyState = SDL_GetKeyboardState(NULL);

	std::memcpy(
		reinterpret_cast<void*>(&PrevKeyboardState[0]),
		reinterpret_cast<const void*>(&CurrKeyboardState[0]),
		static_cast<size_t>(SDL_Scancode::SDL_NUM_SCANCODES)
	);

	std::memcpy(
		reinterpret_cast<void*>(&CurrKeyboardState[0]),
		reinterpret_cast<const void*>(&KeyState[0]),
		static_cast<size_t>(SDL_Scancode::SDL_NUM_SCANCODES)
	);
}

Game::EButtonState Game::KeyboardState::GetKeyState(uint8_t InKeyCode) const
{
	EButtonState OutButtonState = EButtonState::None;

	if (IsPressKey(PrevKeyboardState, InKeyCode))
	{
		if (IsPressKey(CurrKeyboardState, InKeyCode))
		{
			OutButtonState = EButtonState::Held;
		}
		else
		{
			OutButtonState = EButtonState::Released;
		}
	}
	else
	{
		if (IsPressKey(CurrKeyboardState, InKeyCode))
		{
			OutButtonState = EButtonState::Pressed;
		}
		else
		{
			OutButtonState = EButtonState::None;
		}
	}

	return OutButtonState;
}

bool Game::KeyboardState::IsPressKey(const std::vector<uint8_t>& InKeyboardState, uint8_t InKeyCode) const
{
	return InKeyboardState[InKeyCode] == 0 ? false : true;
}