#pragma once

#include "Macro.h"


/**
 * @brief 게임 내에서 사용할 시스템의 인터페이스 클래스입니다.
 */
class ISystem
{
public:
	/**
	 * @brief 게임 내에서 사용할 시스템의 인터페이스 클래스 생성자입니다.
	 */
	ISystem() = default;


	/**
	 * @brief 게임 내에서 사용할 시스템의 인터페이스 클래스 가상 소멸자입니다.
	 */
	virtual ~ISystem() {}


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ISystem);


	/**
	 * @brief 시스템을 초기화합니다.
	 */
	virtual void Setup() = 0;


	/**
	 * @brief 시스템에 할당된 리소스를 정리합니다.
	 */
	virtual void Cleanup() = 0;
};