#pragma once

#include "Macro.h"


/**
 * @brief 게임을 초기화 및 실행하는 프레임워크입니다.
 * 
 * @note 게임이 구현되는 클래스는 이 프레임워크를 반드시 상속받아야 합니다.
 */
class GameFramework
{
public:
	/**
	 * @brief 게임 프레임워크의 생성자입니다.
	 * 
	 * @note 이 생성자는 아무런 초기화도 수행하지 않습니다.
	 */
	GameFramework() = default;


	/**
	 * @brief 게임 프레임워크의 가상 소멸자입니다.
	 */
	virtual ~GameFramework();


	/**
	 * @brief 게임 프레임워크를 초기화합니다.
	 * 
	 * @note 가상 함수로, 반드시 하위 클래스에서 구현해야 합니다.
	 */
	virtual void Init() = 0;


	/**
	 * @brief 게임 프레임워크를 실행합니다.
	 * 
	 * @note 가상 함수로, 반드시 하위 클래스에서 구현해야 합니다.
	 */
	virtual void Run() = 0;
};