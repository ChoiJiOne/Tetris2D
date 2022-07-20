#pragma once

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <memory>

#include "Game/Graphics.h"
#include "Game/Logging.h"
#include "Game/Timer.h"

struct GLFWwindow;


/**
 * 테트리스 게임 클래스입니다.
 */
class Tetris2D
{
public:
	/**
	 * 테트리스 게임 클래스의 생성자입니다.
	 */
	Tetris2D() = default;


	/**
	 * 테트리스 게임 클래스의 소멸자입니다.
	 */
	virtual ~Tetris2D();


	/**
	 * 테트리스 게임을 초기화합니다.
	 */
	void Initialize();


	/**
	 * 테트리스 게임을 실행합니다.
	 */
	void Run();


private:
	/**
	 * 입력 처리를 수행합니다.
	 */
	void ProcessInput();


	/**
	 * 테트리스 게임 루프를 업데이트합니다.
	 */
	void Update();


	/**
	 * 테트리스 게임을 화면에 그립니다.
	 */
	void Draw();



private:
	/**
	 * GLFW 윈도우 및 컨텍스트 입니다.
	 */
	GLFWwindow* Window = nullptr;


	/**
	 * GLFW 윈도우의 가로 크기입니다.
	 */
	int32_t WindowWidth = 1000;
	 
	 
	 /**
	 * GLFW 윈도우의 세로 크기입니다.
	 */
	int32_t WindowHeight = 800;


	/**
	 * 게임 타이머입니다.
	 */
	Game::Timer Timer;


	/**
	 * 2D 렌더링을 위한 그래픽스 인스턴스입니다.
	 */
	Game::Graphics Graphics;
};