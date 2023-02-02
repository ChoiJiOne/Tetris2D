#pragma once

#include "Macro.h"

#include <functional>


/**
 * @brief 게임 씬을 실행합니다.
 */
class Scene
{
public:
	/**
	 * @brief 게임 씬의 기본 생성자입니다.
	 */
	Scene() = default;


	/**
	 * @brief 게임 씬의 가상 소멸자입니다.
	 */
	virtual ~Scene() = default;


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Scene);


	/**
	 * @brief 게임 씬을 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) = 0;


	/**
	 * @brief 씬 전환이 발생했을 때, 실행할 이벤트를 설정합니다.
	 */
	void SetSwitchEvent(const std::function<void()>& SwitchEvent) { SwitchEvent_ = SwitchEvent; }


protected:
	/**
	 * @brief 씬 전환이 발생했을 때, 이벤트를 실행합니다.
	 */
	void RunSwitchEvent()
	{
		if (SwitchEvent_) SwitchEvent_();
	}


private:
	/**
	 * @brief 씬 전환이 발생했을 때, 실행할 이벤트입니다.
	 */
	std::function<void()> SwitchEvent_;
};