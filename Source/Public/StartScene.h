#pragma once

#include "Scene.h"


/**
 * @brief 게임 시작 씬입니다.
 */
class StartScene : public Scene
{
public:
	/**
	 * @brief 게임 시작 씬의 기본 생성자입니다.
	 */
	StartScene() = default;


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
};