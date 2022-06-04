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


	// 복사 생성자 및 대입 연산자입니다.
	GameInput(GameInput&& InInstance) noexcept;
	GameInput& operator=(GameInput&& InInstance) noexcept;


	// 복사 생성자 및 대입 연산자입니다.
	GameInput(const GameInput& InInstance) noexcept;
	GameInput& operator=(const GameInput& InInstance) noexcept;


	// 종료 이벤트 콜백 함수를 설정합니다.
	//
	// @param InExitEventCallback - 종료 이벤트 발생 시 호출할 이벤트입니다.
	void SetExitEventCallback(const std::function<void()>& InExitEventCallback);


	// 키보드의 상태를 업데이트합니다.
	// 이 메서드는 매 프레임 호출되어야 합니다.
	// 
	// @return - SDL 종료 이벤트가 감지되면 false 반환, 그렇지 않으면 true 반환합니다.
	void Tick() noexcept;


private:
	// 종료 이벤트 콜벡 함수입니다.
	std::function<void()> ExitEventCallback = nullptr;
};