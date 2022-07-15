// @third party code - BEGIN SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
// @third party code - END

#include "Logging.h"
#include "Input.h"

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

Game::Input::~Input()
{
}

bool Game::Input::Tick()
{
	bool bIsDetectQuitMessage = false;

	SDL_Event Event;

	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_QUIT)
		{
			bIsDetectQuitMessage = true;
		}
	}

	Keyboard.Update(); 
	Mouse.Update();

	return bIsDetectQuitMessage;
}

Game::MouseState::MouseState()
{
	GetCurrentMouseState(PrevCursorPosition, PrevButtonState);
	GetCurrentMouseState(CurrCursorPosition, CurrButtonState);
}

Game::MouseState::~MouseState()
{
}

void Game::MouseState::Update()
{
	PrevCursorPosition = CurrCursorPosition;
	PrevButtonState = CurrButtonState;

	GetCurrentMouseState(CurrCursorPosition, CurrButtonState);
}

Game::EButtonState Game::MouseState::GetKeyState(const EKeyType& InKeyType) const
{
	EButtonState OutButtonState = EButtonState::None;

	if (IsPressKey(PrevButtonState, InKeyType))
	{
		if (IsPressKey(CurrButtonState, InKeyType))
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
		if (IsPressKey(CurrButtonState, InKeyType))
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

void Game::MouseState::GetCurrentMouseState(Vec2i& InCursorPosition, uint32_t& InButtonState)
{
	InButtonState = SDL_GetMouseState(&InCursorPosition.x, &InCursorPosition.y);
}

bool Game::MouseState::IsPressKey(const uint32_t& InButtonState, const EKeyType& InKeyType) const
{
	uint32_t Mask = 0;

	switch (InKeyType)
	{
	case EKeyType::Left:
		Mask = SDL_BUTTON_LMASK;
		break;

	case EKeyType::Right:
		Mask = SDL_BUTTON_RMASK;
		break;

	default:
		Logging::Warning("undefined mouse key type");
		break;
	}

	return (InButtonState & Mask) == 0 ? false : true;
}
