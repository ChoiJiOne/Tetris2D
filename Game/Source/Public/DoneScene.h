#pragma once

#include <array>

#include "Scene.h"

class Button;


/**
 * @brief 게임 종료 씬입니다.
 */
class DoneScene : public Scene
{
public:
	/**
	 * @brief 게임 종료 씬에서 선택할 수 있는 사항입니다.
	 */
	enum class ESelectState
	{
		NONE   = 0,
		REPLAY = 1,
		RESET  = 2,
		QUIT   = 3,
	};


public:
	/**
	 * @brief 게임 종료 씬의 생성자입니다.
	 */
	DoneScene();


	/**
	 * @brief 게임 종료 씬의 가상 소멸자입니다.
	 */
	virtual ~DoneScene();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(DoneScene);


	/**
	 * @brief 게임 종료 씬을 업데이트합니다.
	 *
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief 게임 종료 씬의 선택 중인 상태를 얻습니다.
	 *
	 * @return 게임 종료 씬의 선택 중인 상태를 반환합니다.
	 */
	ESelectState GetSelectState() const { return CurrentSelectState_; }


private:
	/**
	 * @brief 현재 선택 중인 상태입니다.
	 *
	 * @note 선택 중인 상태의 전환이 발생하면 씬 전환 이벤트가 실행됩니다.
	 */
	ESelectState CurrentSelectState_ = ESelectState::NONE;


	/**
	 * @brief 종료 씬의 버튼입니다.
	 */
	std::array<Button*, 3> Buttons_;
};