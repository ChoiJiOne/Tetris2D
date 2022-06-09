#pragma once

// 표준 라이브러리 및 SDL2를 사용하기 위한 헤더 선언을 추가합니다.
#include "CommonHeader.h"


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


	// Tick 호출 이전에 특정 키가 눌렸는지의 여부를 반환합니다.
	//
	// @param InKeyCode - 키코드 값입니다.
	// @return - 키가 눌렸다면, true, 눌리지 않았다면 false를 반환합니다.
	bool IsPrevKeyPress(uint8_t InKeyCode) noexcept;


	// Tick 호출 이후에 특정 키가 눌렸는지의 여부를 반환합니다.
	//
	// @param InKeyCode - 키코드 값입니다.
	// @return - 키가 눌렸다면, true, 눌리지 않았다면 false를 반환합니다.
	bool IsCurrKeyPress(uint8_t InKeyCode) noexcept;


	// 마우스가 윈도우 창 내부에 있는지 확인합니다.
	//
	// @return 마우스가 윈도우 창 내부에 있는지의 여부를 반환합니다.
	bool IsMouseFocus() noexcept { return bIsMouseFocus; }


private:
	// SDL2의 윈도우 이벤트를 처리합니다.
	// 
	// @param InEventCode - SDL2 윈도우 이벤트입니다.
	void ProcessWindowEvent(const SDL_WindowEvent& InWindowEvent);


	// SDL2 키보드의 상태를 업데이트합니다.
	void UpdateKeyboardState();


	// SDL2 마우스 상태를 업데이트합니다.
	void UpdateMouseState();


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


	// Tick 호출 이전의 윈도우 마우스 X 좌표입니다.
	int32_t PrevMousePositionX = 0;


	// Tick 호출 이전의 윈도우 마우스 Y 좌표입니다.
	int32_t PrevMousePositionY = 0;

	
	// Tick 호출 이전의 윈도우 마우스 상태입니다.
	uint32_t PrevMouseState = 0;


	// Tick 호출 이후의 윈도우 마우스 X 좌표입니다.
	int32_t CurrMousePositionX = 0;


	// Tick 호출 이후의 윈도우 마우스 Y 좌표입니다.
	int32_t CurrMousePositionY = 0;


	// Tick 호출 이후의 윈도우 마우스 상태입니다.
	uint32_t CurrMouseState = 0;


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


	// Tick 호출 이전의 키보드 상태를 나타내는 벡터입니다.
	std::vector<uint8_t> PrevKeyboardState;


	// Tick 호출 이후의 키보드 상태를 나타내는 벡터입니다.
	std::vector<uint8_t> CurrKeyboardState;
};