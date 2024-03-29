#pragma once

#include "Vector.hpp"
#include "Scene.h"

#include <array>
#include <list>

class GameObject;


/**
 * @brief 테트리스 게임의 플레이 씬입니다.
 */
class PlayScene : public Scene
{
public:
	/**
	 * @brief 플레이어의 레벨입니다.
	 * 
	 * @note
	 * LEVEL1 => 업데이트 속도 1.0초
	 * LEVEL2 => 업데이트 속도 0.8초
	 * LEVEL3 => 업데이트 속도 0.6초
	 * LEVEL4 => 업데이트 속도 0.4초
	 * LEVEL5 => 업데이트 속도 0.2초
	 * LEVEL6 => 업데이트 속도 0.1초
	 */
	enum class ELevel : int32_t
	{
		LEVEL1 = 1,
		LEVEL2 = 2,
		LEVEL3 = 3,
		LEVEL4 = 4,
		LEVEL5 = 5,
		LEVEL6 = 6
	};


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


	/**
	 * @brief 유저의 플레이 시간을 얻습니다.
	 * 
	 * @return 유저의 플레이 시간값을 반환합니다.
	 */
	float GetUserPlayTime() const { return PlayTime_; }
	

	/**
	 * @brief 유저가 삭제한 라인 수를 얻습니다.
	 * 
	 * @return 유저가 삭제한 라인 수를 반환합니다.
	 */
	int32_t GetUserRemoveLine();


	/**
	 * @brief 유저의 레벨을 얻습니다.
	 * 
	 * @return 유저의 레벨을 반환합니다.
	 */
	int32_t GetUserLevel() { return static_cast<int32_t>(Level_); }


private:
	/**
	 * @brief 게임 플레이 씬의 기본 오브젝트를 구성합니다.
	 */
	void ConstructBasicObjects();


	/**
	 * @brief 게임 중시 시 존재할 오브젝트를 구성합니다.
	 */
	void ConstructPauseObjects();


	/**
	 * @brief 유저의 플레이 정보를 표시할 오브젝트를 구성합니다.
	 */
	void ConstructUserInfoObjects();


	/**
	 * @brief 다음 테트로미노를 업데이트합니다.
	 */
	void UpdateNextTetromino();


	/**
	 * @brief 유저의 정보를 업데이트합니다.
	 */
	void UpdateUserInfo();


	/**
	 * @brief 유저의 레벨을 증가시킵니다.
	 */
	void LevelUp();


private:
	/**
	 * @brief 게임 플레이 씬의 기본 오브젝트입니다.
	 */
	std::array<GameObject*, 13> BasicObjects_;


	/**
	 * @brief 게임 중지 시 표시할 오브젝트입니다.
	 */
	std::array<GameObject*, 5> PauseObjects_;


	/**
	 * @brief 유저의 플레이 정보를 표시할 오브젝트입니다.
	 */
	std::array<GameObject*, 3> UserInfoObjects_;


	/**
	 * @brief 테트리스의 보드입니다.
	 */
	GameObject* BoardObject_ = nullptr;


	/**
	 * @brief 테트로미노 오브젝트입니다.
	 */
	std::list<GameObject*> TetrominoObjects_;


	/**
	 * @brief 보드의 위치입니다.
	 */
	Vec2f BoardPosition_;


	/**
	 * @brief 테트로미노의 시작 위치입니다.
	 */
	Vec2f StartPosition_;


	/**
	 * @brief 테트로미노의 대기 위치입니다.
	 */
	Vec2f WaitPosition_;


	/**
	 * @brief 현재 테트로미노입니다.
	 */
	int32_t CurrentTetromino_ = 0;


	/**
	 * @brief 생성된 테트로미노의 수입니다.
	 */
	int32_t CountOfTetromino_ = 0;


	/**
	 * @brief 게임이 플레이 중인지 확인합니다.
	 */
	bool bIsPlaying_ = true;


	/**
	 * @brief 유저의 플레이 시간입니다.
	 */
	float PlayTime_ = 0.0f;


	/**
	 * @brief 유저의 레벨입니다.
	 */
	ELevel Level_ = ELevel::LEVEL1;


	/**
	 * @brief 유저의 레벨업 조건입니다.
	 */
	int32_t LevelUpCondition_ = 0;


	/**
	 * @brief 레벨 당 업데이트 해야 할 시간입니다.
	 */
	std::unordered_map<ELevel, float> MappingLevelUpdateSteps_;


	/**
	 * @brief 게임 중지 시 발생할 이벤트입니다.
	 */
	std::function<void()> PauseEvent_ = nullptr;


	/**
	 * @brief 게임을 더이상 진행할 수 없을 때 발생할 이벤트입니다.
	 */
	std::function<void()> GameOverEvent_ = nullptr;
};