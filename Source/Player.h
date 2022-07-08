#pragma once

#include "Game/MathHelper.h"
#include "Game/Font.h"


// 테트리스 게임 플레이어입니다.
class Player
{
public:
	// 플레이어의 상태를 나타냅니다.
	enum class EState : int32_t
	{
		Play = 0, // 플레이 중인 상태를 나타냅니다.
		Wait = 1, // 대기 중인 상태를 나타냅니다.
		Done = 2  // 종료 상태를 나타냅니다.
	};


	// 플레이어의 레벨당 플레이 시간입니다. 단위는 초단위입니다.
	static const int32_t PLAY_TIME_PER_LEVEL = 100;


	// 플레이어의 레벨당 대기 시간입니다. 단위는 초단위입니다.
	static const int32_t WAIT_TIME_PER_LEVEL = 5;


public:
	// 생성자입니다.
	Player() = default;


	// 가상 소멸자입니다.
	virtual ~Player();


	// 게임 플레이어의 레벨을 1 증가시킵니다.
	void LevelUp();


	// 게임 플레이어가 삭제한 라인 수를 추가합니다.
	//
	// @param InRemoveLine - 추가할 라인 수 입니다.
	void AddRemoveLine(int32_t InRemoveLine);


	// 플레이어의 상태를 업데이트합니다.
	//
	// @param InDeltaTime - 델타 시간 값입니다.
	void Update(float InDeltaTime);


	// 플레이어의 현재 상태를 반환합니다.
	//
	// @return - 플레이어의 현재 상태를 반환합니다.
	EState GetCurrentState() const { return CurrentState; }


	// 플레이어의 업데이트 이전 상태를 반환합니다.
	//
	// @return - 플레이어의 이전 상태를 반환합니다.
	EState GetBeforeState() const { return BeforeState; }


	// 플레이어의 상태를 변경합니다.
	//
	// @param InState - 변경할 플레이어의 상태입니다.
	void SetCurrentState(EState InState) { BeforeState = CurrentState; CurrentState = InState; }


	// 스탭 시간의 최대값을 반환합니다.
	//
	// @return - 스탭 시간의 최대값을 반환합니다.
	float GetCurrentMaxStepTime() const { return CurrentMaxStepTime; }


	// 스탭 시간의 최대값을 설정합니다.
	//
	// @param InCurrentMaxStepTime - 설정할 현재 스탭 시간의 최대값입니다.
	void SetCurrentMaxStepTime(float InCurrentMaxStepTime);


	// 스탭 시간을 반환합니다.
	//
	// @return - 스탭 시간을 반환합니다.
	float GetStepTime() const { return StepTime; }


	// 플레이어 레벨을 반환합니다.
	//
	// @return - 플레이어 레벨을 반환합니다.
	int32_t GetLevel() const { return Level; }


	// 게임 플레어어의 모든 요소를 초기화합니다.
	void ResetAllProperties();


	// 게임 플레이어의 레벨을 초기화합니다.
	void ResetLevel();


	// 게임 플레이어가 삭제한 라인 수를 초기화합니다.
	void ResetRemoveLine();


	// 게임 플레이어의 스텝 타임을 초기화합니다.
	void ResetStepTime();
	

	// 플레이어 정보를 화면에 그립니다.
	// 
	// @param InRenderer - SDL 렌더러의 포인터입니다.
	// @param InFont - 텍스트 폰트입니다.
	// @param InWindowPosition - 플레이어 정보를 그릴 윈도우 상의 좌표입니다.
	void Draw(SDL_Renderer* InRenderer, const Game::Font& InFont, const Vec2i& InWindowPosition);


private:
	// 플레이어 정보의 UI Layout을 화면에 그립니다.
	// 
	// @param InRenderer - SDL 렌더러의 포인터입니다.
	// @param InFont - 텍스트 폰트입니다.
	// @param InWindowPosition - 플레이어 정보를 그릴 윈도우 상의 좌표입니다.
	void DrawUILayout(SDL_Renderer* InRenderer, const Game::Font& InFont, const Vec2i& InWindowPosition);


private:
	// 플레이어의 레벨입니다.
	int32_t Level = 0;


	// 플레이어가 삭제한 라인 수입니다.
	int32_t RemoveLine = 0;


	// 업데이트 이전의 플레이어 상태입니다.
	EState BeforeState = EState::Wait;


	// 플레이어의 현재 상태입니다.
	EState CurrentState = EState::Wait;


	// 플레이어의 특정 상태의 경과 시간입니다.
	float StateElapsedTime = 0.0f;


	// 스텝 경과 시간입니다.
	float StepTime = 0.0f;


	// 현재 스탭 시간의 최대값입니다.
	float CurrentMaxStepTime = 1.5f;


	// 스탭 시간의 최소값입니다.
	const float MinStepTime = 0.3f;
};