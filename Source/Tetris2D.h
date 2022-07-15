#pragma once

#include "Game/Logging.h"
#include "Game/Input.h"

#include "Game/Timer.h"
#include "Game/Window.h"
#include "Game/Graphics.h"


// 테트리스 게임을 실행 및 관리하는 클래스입니다.
class Tetris2D
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
	void Setup();


	// 테트리스 게임 루프를 실행합니다.
	void Run();


	// 테트리스 게임 입력 처리를 수행합니다.
	void Input();


	// 테트리스 게임 루프를 업데이트합니다.
	void Update();


	// 테트리스 게임을 화면에 그립니다.
	void Draw();


private:
	/**
	 * 게임 윈도우입니다.
	 */
	Game::Window Window;

	/**
	 * 게임 렌더링을 위한 그래픽스 인스턴스입니다.
	 */
	Game::Graphics Graphics2D;


	// 루프를 종료할 지 확인합니다.
	bool bIsDoneLoop = false;


	// 게임 타이머입니다.
	Game::Timer GameTimer;


	// 게임 폰트키입니다.
	std::size_t FontKey = 0;


	// 게임 텍스처키입니다.
	std::size_t TextureKey = 0;


	// 키보드입니다.
	Game::KeyboardState Keyboard;
};