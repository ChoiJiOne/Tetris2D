#pragma once

// 표준 라이브러리 및 SDL2를 사용하기 위한 헤더 선언을 추가합니다.
#include "CommonHeader.h"


// 키보드 상태를 관리하는 클래스입니다.
class KeyboardState
{
public:
	// 생성자입니다.
	KeyboardState() = default;


	// 가상 소멸자입니다.
	virtual ~KeyboardState();


	// 복사 생성자를 사용할 수 없도록 명시적으로 삭제합니다.
	KeyboardState(KeyboardState&& InInstance) = delete;
	KeyboardState(const KeyboardState& InInstance) = delete;


	// 대입 연산자를 사용할 수 없도록 명시적으로 삭제합니다.
	KeyboardState& operator=(KeyboardState&& InInstance) = delete;
	KeyboardState& operator=(const KeyboardState& InInstance) = delete;


	// 키보드 상태를 초기화합니다.
	void Init();


	// 키보드 상태를 최신화합니다.
	void Update();


	// 업데이트 이전에 특정 키가 눌렸는지의 여부를 반환합니다.
	//
	// @param InKeyCode - 키코드 값입니다.
	// @return - 키가 눌렸다면, true, 눌리지 않았다면 false를 반환합니다.
	bool IsPrevKeyPress(uint8_t InKeyCode) const noexcept;


	// 업데이트 이후에 특정 키가 눌렸는지의 여부를 반환합니다.
	//
	// @param InKeyCode - 키코드 값입니다.
	// @return - 키가 눌렸다면, true, 눌리지 않았다면 false를 반환합니다.
	bool IsCurrKeyPress(uint8_t InKeyCode) const noexcept;


private:
	// 초기화 상태를 나타냅니다.
	bool bIsInitialize = false;


	// 업데이트 이전의 키보드 상태를 나타내는 벡터입니다.
	std::vector<uint8_t> PrevKeyboardState;


	// 업데이트 이후의 키보드 상태를 나타내는 벡터입니다.
	std::vector<uint8_t> CurrKeyboardState;
};


// 마우스 상태를 관리하는 클래스입니다.
class MouseState
{
public:
	// 마우스의 클릭 상태를 나타냅니다.
	enum class ButtonState
	{
		NONE = 0,
		LEFT = 1,
		MIDDLE = 2,
		RIGHT = 3
	};


public:
	// 생성자입니다.
	MouseState() = default;


	// 가상 소멸자입니다.
	virtual ~MouseState();


	// 복사 생성자를 사용할 수 없도록 명시적으로 삭제합니다.
	MouseState(MouseState&& InInstance) = delete;
	MouseState(const MouseState& InInstance) = delete;


	// 대입 연산자를 사용할 수 없도록 명시적으로 삭제합니다.
	MouseState& operator=(MouseState&& InInstance) = delete;
	MouseState& operator=(const MouseState& InInstance) = delete;


	// 마우스 상태를 초기화합니다.
	void Init();


	// 마우스 상태를 최신화합니다.
	void Update();


	// 업데이트 이전의 마우스 X좌표를 반환합니다.
	//
	// @return - 업데이트 이전의 마우스 X좌표를 반환합니다.
	int32_t GetPrevMousePositionX() const { return PrevMousePositionX; }
	
	
	// 업데이트 이전의 마우스 Y좌표를 반환합니다.
	//
	// @return - 업데이트 이전의 마우스 Y좌표를 반환합니다.
	int32_t GetPrevMousePositionY() const { return PrevMousePositionY; }


	// 업데이트 이전의 마우스 위치를 반환합니다.
	//
	// @param OutPositionX - 업데이트 이전의 마우스 X좌표입니다.
	// @param OutPositionY - 업데이트 이전의 마우스 Y좌표입니다.
	void GetPrevMousePosition(int32_t& OutPositionX, int32_t& OutPositionY) const { OutPositionX = PrevMousePositionX; OutPositionY = PrevMousePositionY; }
	

	// 업데이트 이후의 마우스 X좌표를 반환합니다.
	//
	// @return - 업데이트 이후의 마우스 X좌표를 반환합니다.
	int32_t GetCurrMousePositionX() const { return CurrMousePositionX; }
	
	
	// 업데이트 이후의 마우스 Y좌표를 반환합니다.
	//
	// @return - 업데이트 이후의 마우스 Y좌표를 반환합니다.
	int32_t GetCurrMousePositionY() const { return CurrMousePositionY; }


	// 업데이트 이후의 마우스 위치를 반환합니다.
	//
	// @param OutPositionX - 업데이트 이후의 마우스 X좌표입니다.
	// @param OutPositionY - 업데이트 이후의 마우스 Y좌표입니다.
	void GetCurrMousePosition(int32_t& OutPositionX, int32_t& OutPositionY) const { OutPositionX = CurrMousePositionX; OutPositionY = CurrMousePositionY; }


	// 마우스 X좌표의 업데이트 이후와 이전의 차이값을 반환합니다.
	//
	// @return - 마우스 X좌표의 업데이트 이후와 이전의 차이값을 반환합니다.
	int32_t DeltaMousePositionX() const;


	// 마우스 Y좌표의 업데이트 이후와 이전의 차이값을 반환합니다.
	//
	// @return - 마우스 Y좌표의 업데이트 이후와 이전의 차이값을 반환합니다.
	int32_t DeltaMousePositionY() const;


	// 마우스 좌표의 업데이트 이후와 이전의 차이값을 반환합니다.
	//
	// @param OutDeltaX - 마우스 X좌표의 업데이트 이후와 이전의 차이값입니다.
	// @param OutDeltaY - 마우스 Y좌표의 업데이트 이후와 이전의 차이값입니다.
	void DeltaMousePosition(int32_t& OutDeltaX, int32_t& OutDeltaY) const;


	// 업데이트 이전의 마우스 버튼 상태값을 반환합니다.
	//
	// @return - 업데이트 이전의 마우스 버튼 상태값을 반환합니다.
	ButtonState GetPrevMouseButtonState() const;


	// 업데이트 이후의 마우스 버튼 상태값을 반환합니다.
	//
	// @return -업데이트 이후의 마우스 버튼 상태값을 반환합니다.
	ButtonState GetCurrMouseButtonState() const;


private:
	// 초기화 상태를 나타냅니다.
	bool bIsInitialize = false;


	// 업데이트 이전의 윈도우 마우스 X 좌표입니다.
	int32_t PrevMousePositionX = 0;


	// 업데이트 이전의 윈도우 마우스 Y 좌표입니다.
	int32_t PrevMousePositionY = 0;


	// 업데이트 이전의 윈도우 마우스 상태입니다.
	uint32_t PrevMouseButtonState = 0;


	// 업데이트 이후의 윈도우 마우스 X 좌표입니다.
	int32_t CurrMousePositionX = 0;


	// 업데이트 이후의 윈도우 마우스 Y 좌표입니다.
	int32_t CurrMousePositionY = 0;


	// 업데이트 이후의 윈도우 마우스 상태입니다.
	uint32_t CurrMouseButtonState = 0;
};


// 입력 처리를 수행하고 관리하는 클래스입니다.
class GameInput
{
public:
	// 생성자입니다.
	GameInput() = default;


	// 가상 소멸자 입니다.
	virtual ~GameInput();


	// 복사 생성자를 사용할 수 없도록 명시적으로 삭제합니다.
	GameInput(GameInput&& InInstance) = delete;
	GameInput(const GameInput& InInstance) = delete;


	// 대입 연산자를 사용할 수 없도록 명시적으로 삭제합니다.
	GameInput& operator=(GameInput&& InInstance) = delete;
	GameInput& operator=(const GameInput& InInstance) = delete;


	// GameInput을 초기화합니다.
	void Init();


	// 종료 이벤트의 콜백 함수를 설정합니다.
	//
	// @param InQuitEventCallback - 종료 이벤트 발생 시 호출할 함수입니다.
	void SetQuitEventCallback(const std::function<void()>& InQuitEventCallback);


	// 윈도우 크기 변경 이벤트의 콜백 함수를 설정합니다.
	// 
	// @param InResizeEventCallback - 윈도우 크기 변경 이벤트 발생 시 호출할 함수입니다.
	void SetResizeEventCallback(const std::function<void(int32_t, int32_t)>& InResizeEventCallback);


	// 윈도우 최소화 이벤트의 콜백 함수를 설정합니다.
	//
	// @param InMinimizeEventCallback - 윈도우 최소화 이벤트 발생 시 호출할 함수입니다.
	void SetMinimizeEventCallback(const std::function<void()>& InMinimizeEventCallback);


	// 윈도우 최대화 이벤트의 콜백 함수를 설정합니다.
	//
	// @param InMaximizeEventCallback - 윈도우 최대화 이벤트 발생 시 호출할 함수입니다.
	void SetMaximizeEventCallback(const std::function<void()>& InMaximizeEventCallback);


	// 윈도우 활성화 이벤트의 콜백 함수를 설정합니다.
	//
	// @param InActiveWindowCallback - 윈도우 활성화 이벤트 발생 시 호출할 함수입니다.
	void SetActiveWindowCallback(const std::function<void()>& InActiveWindowCallback);


	// 윈도우 비활성화 이벤트의 콜백 함수를 설정합니다.
	//
	// @param InInactiveWindowCallback - 윈도우 비활성화 이벤트 발생 시 호출할 함수입니다.
	void SetInactiveWindowCallback(const std::function<void()>& InInactiveWindowCallback);


	// 윈도우 출력 이벤트의 콜백 함수를 설정합니다.
	//
	// @param InExposeWindowCallback - 윈도우 출력 이벤트 발생 시 호출할 함수입니다.
	void SetExposeWindowCallback(const std::function<void()>& InExposeWindowCallback);


	// 입력 상태를 업데이트합니다.
	// 이 메서드는 매 프레임 호출되어야 합니다.
	void Tick() noexcept;


	// 마우스가 윈도우 창 내부에 있는지 확인합니다.
	//
	// @return 마우스가 윈도우 창 내부에 있는지의 여부를 반환합니다.
	bool IsMouseFocus() noexcept { return bIsMouseFocus; }


	// 키보드 상태를 반환합니다.
	//
	// @return KeyboardState의 상수 참조자를 반환합니다.
	const KeyboardState& GetKeyboardState() const { return GameKeyboardState; }


	// 마우스의 상태를 반환합니다.
	//
	// @return MouseState의 상수 참조자를 반환합니다.
	const MouseState& GetMouseState() const { return GameMouseState; }


private:
	// SDL2의 윈도우 이벤트를 처리합니다.
	// 
	// @param InEventCode - SDL2 윈도우 이벤트입니다.
	void ProcessWindowEvent(const SDL_WindowEvent& InWindowEvent);


private:
	// GameInput 초기화 상태를 확인합니다.
	bool bIsInitialize = false;


	// 마우스가 윈도우 창 내부에 있는지 확인합니다.
	bool bIsMouseFocus = false;


	// 윈도우 창이 활성화되어 있는지 확인합니다.
	bool bIsActiveWindow = false;


	// 윈도우 창의 최대화 여부를 확인합니다.
	bool bIsMaximized = false;


	// 윈도우 창의 최소화 여부를 확인합니다.
	bool bIsMinimized = false;


	// 키보드 상태입니다.
	KeyboardState GameKeyboardState;


	// 마우스의 상태입니다.
	MouseState GameMouseState;


	// 종료 이벤트의 콜벡 함수입니다.
	std::function<void()> QuitEventCallback = nullptr;


	// 윈도우 크기 변경 이벤트의 콜백 함수입니다.
	std::function<void(int32_t, int32_t)> ResizeEventCallback = nullptr;


	// 윈도우 최소화 이벤트의 콜백 함수입니다.
	std::function<void()> MinimizeEventCallback = nullptr;
	
	
	// 윈도우 최대화 이벤트의 콜백 함수입니다.
	std::function<void()> MaximizeEventCallback = nullptr;


	// 윈도우 활성화 이벤트의 콜백 함수입니다.
	std::function<void()> ActiveWindowCallback = nullptr;


	// 윈도우 비활성화 이벤트의 콜백 함수입니다.
	std::function<void()> InactiveWindowCallback = nullptr;


	// 윈도우 출력 이벤트의 콜백 함수입니다.
	std::function<void()> ExposeWindowCallback = nullptr;
};