#pragma once

// 표준 라이브러리 및 SDL2를 사용하기 위한 헤더 선언을 추가합니다.
#include "CommonHeader.h"

// 게임 엔진 기능을 사용하기 위한 헤더 선언을 추가합니다.
#include "GameEngine.h"

// 게임 폰트를 사용하기 위한 헤더 선언을 추가합니다.
#include "GameFont.h"

// 게임 입력 처리를 수행하기 위한 헤더 선언을 추가합니다.
#include "GameInput.h"

// 게임 렌더링을 수행하기 위한 헤더 선언을 추가합니다.
#include "GameRenderer.h"

// 게임 타이머를 사용하기 위한 헤더 선언을 추가합니다.
#include "GameTimer.h"

// 게임 윈도우를 생성 및 관리하기 위한 헤더 선언을 추가합니다.
#include "GameWindow.h"

// 로그 기능을 사용하기 위한 헤더 선언을 추가합니다.
#include "Logger.h"

// 매크로 함수를 사용하기 위한 헤더 선언을 추가합니다.
#include "Macro.h"

// 문자열 기능을 사용하기 위한 헤더 선언을 추가합니다.
#include "StringUtil.h"

// 테트로미노를 사용하기 위한 헤더 선언을 추가합니다.
#include "Tetromino.h"

// 테트리스 보드를 사용하기 위한 헤더 선언을 추가합니다.
#include "Board.h"


// 게임 클래스입니다.
class Tetris
{
public:
	// 생성자입니다.
	Tetris() = default;


	// 가상소멸자입니다.
	virtual ~Tetris();


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


	// 게임을 업데이트합니다.
	void Update();


	// 게임을 백 버퍼에 렌더링합니다.
	void Draw();

	void UpdatePlay();
	void UpdateWait();
	void UpdateTitleScene();
	void UpdateEndingScene();

	void DrawPlay();
	void DrawWait();
	void DrawTitleScene();
	void DrawEndingScene();


private:
	// 게임 루프 종료 여부입니다.
	bool bIsDone = false;


	// 게임 중단 여부입니다.
	bool bIsPaused = false;


	// 게임 내의 타이머입니다.
	GameTimer Timer;


	// 게임 폰트입니다.
	GameFont Font;

	std::unordered_map<std::string, Vec2i> uiPositionCache;

	bool bIsStartGame = false;
	bool bIsDoneGame = false;
	bool bIsExitGame = false;
	bool bIsWaitNextLevel = true;

	std::shared_ptr<Board>     tetrisBoard = nullptr;
	std::shared_ptr<Tetromino> currTetromino = nullptr;
	std::shared_ptr<Tetromino> nextTetromino = nullptr;

	int32_t userLevel = 0;
	int32_t userRemoveLine = 0;
	float userPlayTime = 0.0f;
	float userStepTime = 0.0f;
	float waitTime = 0.0f;

	float gameStepTime = 1.5f;
	const float gamePlayTime = 100.0f;
	const float gameWaitTime = 3.0f;
};