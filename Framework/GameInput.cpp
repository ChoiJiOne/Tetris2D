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
        GameKeyboardState.Init();
        GameMouseState.Init();

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

    GameKeyboardState.Update();
    GameMouseState.Update();
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

KeyboardState::~KeyboardState()
{
}

void KeyboardState::Init()
{
    if (!bIsInitialize)
    {
        PrevKeyboardState.resize(SDL_Scancode::SDL_NUM_SCANCODES);
        CurrKeyboardState.resize(SDL_Scancode::SDL_NUM_SCANCODES);

        bIsInitialize = true;
    }
}

void KeyboardState::Update()
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

bool KeyboardState::IsPrevKeyPress(uint8_t InKeyCode) const noexcept
{
    return PrevKeyboardState[InKeyCode] == 0 ? false : true;
}

bool KeyboardState::IsCurrKeyPress(uint8_t InKeyCode) const noexcept
{
    return CurrKeyboardState[InKeyCode] == 0 ? false : true;
}

MouseState::~MouseState()
{
}

void MouseState::Init()
{
    if (!bIsInitialize)
    {
        PrevMouseButtonState = SDL_GetMouseState(&PrevMousePositionX, &PrevMousePositionY);

        CurrMousePositionX = PrevMousePositionX;
        CurrMousePositionY = PrevMousePositionY;
        CurrMouseButtonState = PrevMouseButtonState;

        bIsInitialize = true;
    }
}

void MouseState::Update()
{
    PrevMousePositionX = CurrMousePositionX;
    PrevMousePositionY = CurrMousePositionY;
    PrevMouseButtonState = CurrMouseButtonState;

    CurrMouseButtonState = SDL_GetMouseState(&CurrMousePositionX, &CurrMousePositionY);
}

int32_t MouseState::DeltaMousePositionX() const
{
    return CurrMousePositionX - PrevMousePositionX;
}

int32_t MouseState::DeltaMousePositionY() const
{
    return CurrMousePositionY - PrevMousePositionY;
}

void MouseState::DeltaMousePosition(int32_t& OutDeltaX, int32_t& OutDeltaY) const
{
    OutDeltaX = DeltaMousePositionX();
    OutDeltaY = DeltaMousePositionY();
}

bool MouseState::IsPrevPressMouseButton(EMouseButton InButton) const
{
    return IsPressMouseButton(InButton, CurrMouseButtonState);
}

bool MouseState::IsCurrPressMouseButton(EMouseButton InButton) const
{
    return IsPressMouseButton(InButton, PrevMouseButtonState);
}

bool MouseState::IsPressMouseButton(EMouseButton InButton, uint32_t InButtonState) const
{
    int32_t ButtonMask = 0;

    switch (InButton)
    {
    case EMouseButton::LEFT:
        ButtonMask = SDL_BUTTON(SDL_BUTTON_LEFT);
        break;

    case EMouseButton::RIGHT:
        ButtonMask = SDL_BUTTON(SDL_BUTTON_RIGHT);
        break;

    case EMouseButton::MIDDLE:
        ButtonMask = SDL_BUTTON(SDL_BUTTON_MIDDLE);
        break;

    default:
        Logger::Warning("not support mouse button");
    }

    return InButtonState & ButtonMask;
}
