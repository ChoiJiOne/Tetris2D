#pragma once

#include "GameObject.h"


/**
 * @brief 백그라운드입니다.
 */
class Background : public GameObject
{
public:
	/**
	 * @brief 백그라운드의 생성자입니다.
	 *
	 * @param Signature 백그라운드의 식별자입니다.
	 */
	Background(const std::string& Signature);


	/**
	 * @brief 백그라운드의 가상 소멸자입니다.
	 */
	virtual ~Background() {}


	/**
	 * @brief 명시적으로 복사 생성자외 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Background);


	/**
	 * @brief 백그라운드를 업데이트합니다.
	 *
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;
};