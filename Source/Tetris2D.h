#pragma once

#include "Engine.h"
#include "Window.h"


/**
 * 테트리스 게임 클래스입니다.
 */
class Tetris2D : public Game::Engine
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
	 * @note 이 메서드는 Engine의 Initialize 메서드를 재정의합니다.
	 */
	virtual void Initialize() override;


	/**
	 * 테트리스 게임 입력 처리를 수행합니다.
	 * @note 이 메서드는 Engine의 Input 메서드를 재정의합니다.
	 */
	virtual void Input() override;


	/**
	 * 테트리스 게임 루프를 업데이트합니다.
	 * @note 이 메서드는 Engine의 Update 메서드를 재정의합니다.
	 */
	virtual void Update() override;


	/**
	 * 테트리스 게임을 렌더링합니다.
	 * @note 이 메서드는 Engine의 Render 메서드를 재정의합니다.
	 */
	virtual void Render() override;


	/**
	 * 테트리스 게임 루프를 실행합니다.
	 * @note 이 메서드는 Engine의 Run 메서드를 재정의합니다.
	 */
	virtual void Run() override;


private:
	Game::Window Window;
};