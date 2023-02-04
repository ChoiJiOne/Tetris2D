#pragma once

#include "Scene.h"

#include <vector>

class GameObject;


/**
 * @brief 테트리스 게임의 시작 씬입니다.
 */
class StartScene : public Scene
{
public:
	/**
	 * @brief 테트리스 게임의 시작 씬의 생성자입니다.
	 */
	StartScene();


	/**
	 * @brief 테트리스 게임의 시작 씬의 가상 소멸자입니다.
	 */
	virtual ~StartScene();


	/**
	 * @brief 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartScene);


	/**
	 * @brief 시작 씬을 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Update(float DeltaSeconds) override;


private:
	/**
	 * @brief 시작 씬의 오브젝트입니다.
	 */
	std::vector<GameObject*> SceneObjects_;
};