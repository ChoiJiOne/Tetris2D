#pragma once

// 게임 엔진을 사용하기 위한 헤더 선언을 추가합니다.
#include "GameInterface.h"

// 게임 보드를 사용하기 위한 헤더 선언을 추가합니다.
#include "Board.h"

// 테트로미노를 사용하기 위한 헤더 선언을 추가합니다.
#include "Tetromino.h"


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
	// 전체 게임 관련 리소스를 초기화합니다.
	//
	// @throws - 초기화에 실패할 경우, C++ 표준 예외를 반환합니다.
	void SetupCommonProperties();


	// 테트리스 게임 관련 리소스를 초기화합니다.
	//
	// @throws - 초기화에 실패할 경우, C++ 표준 예외를 반환합니다.
	void SetupTetrisProperties();


private:
	// 게임 루프 종료 여부입니다.
	bool bIsDone = false;


	// 게임 중단 여부입니다.
	bool bIsPaused = false;


	// 게임 내의 타이머입니다.
	GameTimer Timer;


	// 게임 폰트입니다.
	GameFont Font;


	// 테트리스 보드입니다.
	Board TetrisBoard;


	// 현재 보드 상에 위치한 테트로미노입니다.
	std::shared_ptr<Tetromino> CurrTetromino = nullptr;


	// 다음에 보드에 위치할 테트로미노입니다.
	std::shared_ptr<Tetromino> NextTetromino = nullptr;
};