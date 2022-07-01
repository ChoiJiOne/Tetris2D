#pragma once

// 게임 프레임워크를 사용하기 위한 헤더를 선언합니다.
#include "Game/GameFramework.h"


// 테트리스 게임을 실행 및 관리하는 클래스입니다.
class Tetris2D : public Game::Framework
{
public:
	// 생성자입니다.
	Tetris2D() = default;


	// 가상 소멸자입니다.
	virtual ~Tetris2D();


	// 테트리스 게임을 초기화합니다.
	virtual void Setup() override;


	// 테트리스 게임 루프를 실행합니다.
	virtual void Run() override;


	// 테트리스 게임 루프를 업데이트합니다.
	virtual void Update() override;


	// 테트리스 게임을 화면에 그립니다.
	virtual void Draw() override;


private:
	// SDL 윈도우 포인터입니다.
	SDL_Window* Window = nullptr;


	// SDL 렌더러 포인터입니다.
	SDL_Renderer* Renderer = nullptr;


	// 루프를 종료할 지 확인합니다.
	bool bIsDoneLoop = false;
};