#pragma once

#include "Scene.h"

#include <vector>

class GameObject;


/**
 * @brief 테트리스 게임의 플레이 씬입니다.
 */
class PlayScene : public Scene
{
public:
	/**
	 * @brief 테트리스 게임의 플레이 씬의 생성자입니다.
	 */
	PlayScene();


	/**
	 * @brief 테트리스 게임의 플레이 씬의 가상 소멸자입니다.
	 */
	virtual ~PlayScene();


	/**
	 * @brief 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PlayScene);


	/**
	 * @brief 플레이 씬을 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Update(float DeltaSeconds) override;


	/**
	 * @brief 플레이 씬을 초기화합니다.
	 */
	virtual void Reset() override;


	/**
	 * @brief 플레이 씬을 강제로 중지합니다.
	 */
	void EnforcePause();


private:
	/**
	 * @brief 게임이 플레이 중인지 확인합니다.
	 */
	bool bIsPlaying = true;


	/**
	 * @brief 게임 중지 시 발생할 이벤트입니다.
	 */
	std::function<void()> PauseEvent_ = nullptr;


	/**
	 * @brief 게임을 더이상 진행할 수 없을 때 발생할 이벤트입니다.
	 */
	std::function<void()> GameOverEvent_ = nullptr;
};