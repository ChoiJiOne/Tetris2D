#pragma once

#include "Vector.hpp"
#include "Scene.h"


/**
 * @brief 게임 플레이 씬입니다.
 */
class PlayScene : public Scene
{
public:
	/**
	 * @brief 게임 플레이 상태입니다.
	 */
	enum class EState : int32_t
	{
		NONE  = 0,
		PLAY  = 1,
		PAUSE = 2,
		DONE  = 3,
	};


public:
	/**
	 * @brief 게임 플레이 씬의 기본 생성자입니다.
	 */
	PlayScene() = default;


	/**
	 * @brief 게임 플레이 씬의 가상 소멸자입니다
	 */
	virtual ~PlayScene();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PlayScene);


	/**
	 * @brief 게임 플레이 씬을 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief 게임 플레이 씬을 리셋합니다.
	 */
	void Reset();


	/**
	 * @brief 게임이 종료되었는지 확인합니다.
	 * 
	 * @return 게임이 종료되었다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	EState GetCurrentState() const { return CurrentState_; }


private:
	/**
	 * @brief 현재 게임 씬의 상태입니다.
	 */
	EState CurrentState_ = EState::NONE;


	/**
	 * @brief 월드 상의 카메라 중심 위치입니다.
	 */
	Vec2f CameraPosition_;


	/**
	 * @brief 월드 상의 타일 맵의 중심 위치입니다.
	 */
	Vec2f TileMapPosition_;


	/**
	 * @brief 테트로미노의 시작 위치입니다.
	 */
	Vec2i StartPosition_;


	/**
	 * @brief 테트로미노의 대기 위치입니다.
	 */
	Vec2i WaitPosition_;


	/**
	 * @brief 생성된 테트로미노 수입니다.
	 */
	int32_t CountOfTetromino_ = 0;


	/**
	 * @brief 현재 테트로미노의 번호입니다.
	 */
	int32_t CurrentTetromino_ = 0;
};