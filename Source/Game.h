#pragma once

// 게임 타이머를 사용하기 위한 헤더 선언을 추가합니다.
#include "GameTimer.h"

// 게임 윈도우를 생성 및 관리하기 위한 헤더 선언을 추가합니다.
#include "GameWindow.h"

// 전역 요소들을 사용하기 위한 헤더 선언을 추가합니다.
#include "GlobalProperty.h"

// 로그 기능을 사용하기 위한 헤더 선언을 추가합니다.
#include "Logger.h"


// 게임 클래스입니다.
class Game
{
public:
	// 생성자입니다.
	Game() = default;


	// 가상소멸자입니다.
	virtual ~Game();


	// 게임 프레임워크 및 전체 게임을 초기화합니다.
	void Setup();


	// 게임을 실행합니다.
	void Run();


private:
	// 게임 내의 전역 타이머입니다.
	std::unique_ptr<GameTimer> GlobalTimer = nullptr;


	// 게임 윈도우입니다.
	std::unique_ptr<GameWindow> Window = nullptr;
};