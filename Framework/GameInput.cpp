#include "GameInput.h"

GameInput::~GameInput()
{
}

GameInput::GameInput(GameInput&& InInstance) noexcept
    : ExitEventCallback(InInstance.ExitEventCallback)
    , ResizeEventCallback(InInstance.ResizeEventCallback)
{
}

GameInput& GameInput::operator=(GameInput&& InInstance) noexcept
{
    if (this == &InInstance) return *this;

    ExitEventCallback = InInstance.ExitEventCallback;
    ResizeEventCallback = InInstance.ResizeEventCallback;

    return *this;
}

GameInput::GameInput(const GameInput& InInstance) noexcept
    : ExitEventCallback(InInstance.ExitEventCallback)
    , ResizeEventCallback(InInstance.ResizeEventCallback)
{
}

GameInput& GameInput::operator=(const GameInput& InInstance) noexcept
{
    if (this == &InInstance) return *this;

    ExitEventCallback = InInstance.ExitEventCallback;
    ResizeEventCallback = InInstance.ResizeEventCallback;

    return *this;
}

void GameInput::SetExitEventCallback(const std::function<void()>& InExitEventCallback)
{
    ExitEventCallback = InExitEventCallback;
}

void GameInput::SetResizeEventCallback(const std::function<void(int32_t, int32_t)>& InResizeEventCallback)
{
    ResizeEventCallback = InResizeEventCallback;
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

        if (EventMessage.type == SDL_WINDOWEVENT && EventMessage.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            int32_t Width = EventMessage.window.data1;
            int32_t Height = EventMessage.window.data1;
            ResizeEventCallback(Width, Height);
        }
    }
}