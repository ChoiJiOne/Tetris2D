#pragma once

// 게임 프레임워크를 사용하기 위한 헤더를 선언합니다.
#include "Game/Framework.h"

// 게임 타이머를 사용하기 위한 헤더를 선언합니다.
#include "Game/Timer.h"

// 게임 폰트를 사용하기 위한 헤더를 선언합니다.
#include "Game/Font.h"

// 게임 로그를 사용하기 위한 헤더를 선언합니다.
#include "Game/Logger.h"

// 테트로미노를 사용하기 위한 헤더를 선언합니다.
#include "Tetromino.h"

// 테트리스 보드를 사용하기 위한 헤더를 선언합니다.
#include "Board.h"

// 게임 플레이어를 사용하기 위한 헤더를 선언합니다.
#include "Player.h"


// 테트리스 게임을 실행 및 관리하는 클래스입니다.
class Tetris2D : public Game::Framework
{
public:
	// 생성자입니다.
	Tetris2D() = default;


	// 가상 소멸자입니다.
	virtual ~Tetris2D();


	// 복사 생성자를 사용할 수 없도록 명시적으로 삭제합니다. 
	Tetris2D(Tetris2D&& InInstance) = delete;
	Tetris2D(const Tetris2D& InInstance) = delete;


	// 대입 연산자를 사용할 수 없도록 명시적으로 삭제합니다.
	Tetris2D& operator=(Tetris2D&& InInstance) = delete;
	Tetris2D& operator=(const Tetris2D& InInstance) = delete;


	// 테트리스 게임을 초기화합니다.
	virtual void Setup() override;


	// 테트리스 게임 루프를 실행합니다.
	virtual void Run() override;


	// 테트리스 게임 입력 처리를 수행합니다.
	virtual void Input() override;


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


	// 게임 타이머입니다.
	Game::Timer GameTImer;


	// 게임 폰트입니다.
	std::unique_ptr<Game::Font> Font = nullptr;
};