#include "StringUtil.h"
#include "Logger.h"
#include "GameInput.h"

GameInput::~GameInput()
{
    bIsInitialize = false;
}

void GameInput::Init()
{
    if (!bIsInitialize)
    {
        PrevKeyboardState.resize(SDL_Scancode::SDL_NUM_SCANCODES);
        CurrKeyboardState.resize(SDL_Scancode::SDL_NUM_SCANCODES);

        bIsInitialize = true;
    }
}

void GameInput::SetQuitEventCallback(const std::function<void()>& InQuitEventCallback)
{
    QuitEventCallback = InQuitEventCallback;
}

void GameInput::SetResizeEventCallback(const std::function<void(int32_t, int32_t)>& InResizeEventCallback)
{
    ResizeEventCallback = InResizeEventCallback;
}

void GameInput::SetMinimizeEventCallback(const std::function<void()>& InMinimizeEventCallback)
{
    MinimizeEventCallback = InMinimizeEventCallback;
}

void GameInput::SetMaximizeEventCallback(const std::function<void()>& InMaximizeEventCallback)
{
    MaximizeEventCallback = InMaximizeEventCallback;
}

void GameInput::SetActiveWindowCallback(const std::function<void()>& InActiveWindowCallback)
{
    ActiveWindowCallback = InActiveWindowCallback;
}

void GameInput::SetInactiveWindowCallback(const std::function<void()>& InInactiveWindowCallback)
{
    InactiveWindowCallback = InInactiveWindowCallback;
}

void GameInput::SetExposeWindowCallback(const std::function<void()>& InExposeWindowCallback)
{
    ExposeWindowCallback = InExposeWindowCallback;
}

void GameInput::Tick() noexcept
{
    bool bIsUpdate = false;
    SDL_Event EventMessage = {};

    while (SDL_PollEvent(&EventMessage))
    {
        bIsUpdate = true;

        if (EventMessage.type == SDL_QUIT)
        {
            QuitEventCallback();
        }

        if (EventMessage.type == SDL_WINDOWEVENT)
        {
            ProcessWindowEvent(EventMessage.window);
        }
    }

    UpdateKeyboardState();
    UpdateMouseState();
}

void GameInput::ProcessWindowEvent(const SDL_WindowEvent& InWindowEvent)
{
    SDL_Event Event;
    int32_t ChangeWindowWidth = 0;
    int32_t ChangeWindowHeight = 0;

    switch (InWindowEvent.event)
    {
    case SDL_WINDOWEVENT_SIZE_CHANGED:
        bIsMinimized = false;
        bIsMaximized = false;

        ChangeWindowWidth  = InWindowEvent.data1;
        ChangeWindowHeight = InWindowEvent.data2;

        ResizeEventCallback(ChangeWindowWidth, ChangeWindowHeight);
        break;


    case SDL_WINDOWEVENT_EXPOSED:
        ExposeWindowCallback();
        break;


    case SDL_WINDOWEVENT_ENTER:
        bIsMouseFocus = true;
        break;


    case SDL_WINDOWEVENT_LEAVE:
        bIsMouseFocus = false;
        break;


    case SDL_WINDOWEVENT_FOCUS_GAINED:
        bIsActiveWindow = true;
        ActiveWindowCallback();
        break;


    case SDL_WINDOWEVENT_FOCUS_LOST:
        bIsActiveWindow = false;
        InactiveWindowCallback();
        break;


    case SDL_WINDOWEVENT_MINIMIZED:
        bIsMinimized = true;
        bIsMaximized = false;
        MinimizeEventCallback();
        break;


    case SDL_WINDOWEVENT_MAXIMIZED:
        bIsMinimized = false;
        bIsMaximized = true;
        MaximizeEventCallback();
        break;


    case SDL_WINDOWEVENT_RESTORED:
        ExposeWindowCallback();
        break;


    case SDL_WINDOWEVENT_CLOSE:
        Event.type = SDL_QUIT;
        SDL_PushEvent(&Event);
        break;


    default:
        break;
    }
}

void GameInput::UpdateKeyboardState()
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

void GameInput::UpdateMouseState()
{
    PrevMousePositionX = CurrMousePositionX;
    PrevMousePositionY = CurrMousePositionY;
    PrevMouseState = CurrMouseState;

    CurrMouseState = SDL_GetMouseState(&CurrMousePositionX, &CurrMousePositionY);
}

bool GameInput::IsPrevKeyPress(uint8_t InKeyCode) noexcept
{
    return PrevKeyboardState[InKeyCode] == 0 ? false : true;
}

bool GameInput::IsCurrKeyPress(uint8_t InKeyCode) noexcept
{
    return CurrKeyboardState[InKeyCode] == 0 ? false : true;
}