#pragma once

#include "Scene.h"

#include <vector>
#include <functional>

class Button;


/**
 * @brief 테트리스 게임의 씬입니다.
 */
class GameScene : public Scene
{
public:
	/**
	 * @brief 테트리스 게임 씬의 기본 생성자입니다.
	 */
	GameScene() = default;


	/**
	 * @brief 테트리스 게임 씬의  가상 소멸자입니다.
	 */
	virtual ~GameScene() = default;


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameScene);


	/**
	 * @brief 테트리스 게임 씬 내의 버튼을 업데이트합니다.
	 *
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


protected:
	/**
	 * @brief 씬 내의 버튼입니다.
	 */
	std::vector<Button*> SceneButton_;
};