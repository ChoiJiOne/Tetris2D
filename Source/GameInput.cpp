#include "GameInput.h"

GameInput::~GameInput()
{
}

GameInput::GameInput(GameInput&& InInstance) noexcept
    : ExitEventCallback(InInstance.ExitEventCallback)
{
}

GameInput& GameInput::operator=(GameInput&& InInstance) noexcept
{
    if (this == &InInstance) return *this;

    ExitEventCallback = InInstance.ExitEventCallback;

    return *this;
}

GameInput::GameInput(const GameInput& InInstance) noexcept
    : ExitEventCallback(InInstance.ExitEventCallback)
{
}

GameInput& GameInput::operator=(const GameInput& InInstance) noexcept
{
    if (this == &InInstance) return *this;

    ExitEventCallback = InInstance.ExitEventCallback;

    return *this;
}

void GameInput::SetExitEventCallback(const std::function<void()>& InExitEventCallback)
{
    ExitEventCallback = InExitEventCallback;
}

void GameInput::Tick() noexcept
{
    SDL_Event EventMessage = {};

    while (SDL_PollEvent(&EventMessage))
    {
        if (EventMessage.type == SDL_QUIT)
        {
            ExitEventCallback();
        }
    }
}