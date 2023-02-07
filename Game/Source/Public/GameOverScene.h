#pragma once

#include "Scene.h"

#include <vector>

class GameObject;


/**
 * @brief 테트리스 게임의 종료 씬입니다.
 */
class GameOverScene : public Scene
{
public:
	/**
	 * @brief 테트리스 게임의 종료 씬의 생성자입니다.
	 */
	GameOverScene();


	/**
	 * @brief 테트리스 게임의 종료 씬의 가상 소멸자입니다.
	 */
	virtual ~GameOverScene();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameOverScene);


	/**
	 * @brief 종료 신을 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Update(float DeltaSeconds) override;


	/**
	 * @brief 종료 씬을 리셋합니다.
	 */
	virtual void Reset() override;
};