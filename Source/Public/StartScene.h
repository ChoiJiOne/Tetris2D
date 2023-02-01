#pragma once

#include "Scene.h"


/**
 * @brief 게임 시작 씬입니다.
 */
class StartScene : public Scene
{
public:
	/**
	 * @brief 게임 시작 씬의 상태입니다.
	 */
	enum class EState
	{
		NONE    = 0,
		START   = 1,
		SETTING = 2,
		QUIT    = 3,
	};

	
public:
	/**
	 * @brief 게임 시작 씬의 생성자입니다.
	 */
	StartScene();


	/**
	 * @brief 게임 시작 씬의 가상 소멸자입니다.
	 */
	virtual ~StartScene();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartScene);


	/**
	 * @brief 게임 시작 씬을 업데이트합니다.
	 *
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;

	
	/**
	 * @brief 게임 시작 씬의 현재 상태를 얻습니다.
	 * 
	 * @return 게임 시작 씬의 현재 상태를 반환합니다.
	 */
	EState GetCurrentState() const { return CurrentState_; }


private:
	/**
	 * @brief 게임 시작 씬의 상태입니다.
	 * 
	 * @note 선택 중인 상태의 전환이 발생하면 씬 전환 이벤트가 실행됩니다.
	 */
	EState CurrentState_ = EState::NONE;
};