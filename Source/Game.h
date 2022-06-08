#pragma once

// 게임 프레임워크를 사용하기 위한 헤더 선언을 추가합니다.
#include "GameFramework.h"


// 게임 클래스입니다.
class Game : public GameFramework
{
public:
	// 생성자입니다.
	Game() = default;


	// 가상소멸자입니다.
	virtual ~Game();


	// 게임 프레임워크 및 전체 게임을 초기화합니다.
	virtual void Setup() override;


	// 게임을 실행합니다.
	virtual void Run() override;


private:
	// 게임 종료 여부입니다.
	bool bIsExit = false;


	// 게임 내의 전역 타이머입니다.
	GameTimer GlobalTimer;


	// 게임 폰트입니다.
	GameFont Font;
};