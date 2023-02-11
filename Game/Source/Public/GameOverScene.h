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


	/**
	 * @brief 유저의 플레이 정보를 설정합니다.
	 * 
	 * @param PlayTime 유저가 플레이한 시간입니다.
	 * @param RemoveLine 유저가 삭제한 라인 수입니다.
	 * @param Level 유저의 레벨입니다.
	 */
	void SetUserInfo(const float& PlayTime, const int32_t& RemoveLine, const int32_t& Level)
	{
		PlayTime_ = PlayTime;
		RemoveLine_ = RemoveLine;
		Level_ = Level;
	}


private:
	/**
	 * @brief 씬 내의 게임 오브젝트입니다.
	 */
	std::vector<GameObject*> SceneObjects_;


	/**
	 * @brief 유저의 플레이 시간입니다.
	 */
	float PlayTime_ = 0.0f;


	/**
	 * @brief 유저삭제한 라인 수입니다.
	 */
	int32_t RemoveLine_ = 0;


	/**
	 * @brief 유저의 레벨입니다.
	 */
	int32_t Level_ = 0;
};