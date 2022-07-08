#pragma once

#include "Game/MathHelper.h"
#include "Game/Font.h"


// 테트리스 게임 플레이어입니다.
class Player
{
public:
	// 플레이어의 플레이 시간입니다. 단위는 초단위입니다.
	static const int32_t PLAY_TIME = 100;


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


	// 플레이어의 남은 시간을 업데이트합니다.
	//
	// @param InDeltaTime - 델타 시간 값입니다.
	void UpdateRemainTime(float InDeltaTime);


	// 게임 플레이어의 플레이 타임이 끝났는지 확인합니다.
	//
	// @return - 게임 플레이어의 플레이 타임이 끝났다면 true, 그렇지 않다면 false를 반환합니다.
	bool IsOverPlayTime();


	// 게임 플레어어의 모든 요소를 초기화합니다.
	void ResetAllProperties();


	// 게임 플레이어의 레벨을 초기화합니다.
	void ResetLevel();


	// 게임 플레이어가 삭제한 라인 수를 초기화합니다.
	void ResetRemoveLine();


	// 게임 플레이어의 남은 시간을 초기화합니다.
	void ResetRemainTime();


	// 게임 플레이어의 대기 시간을 초기화합니다.
	void ResetWaitTime();


	// 플레이어 정보를 화면에 그립니다.
	// 
	// @param InRenderer - SDL 렌더러의 포인터입니다.
	// @param InFont - 텍스트 폰트입니다.
	// @param InWindowPosition - 플레이어 정보를 그릴 윈도우 상의 좌표입니다.
	void Draw(SDL_Renderer* InRenderer, const Game::Font& InFont, const Vec2i& InWindowPosition);


private:
	// 플레이어의 레벨입니다.
	int32_t Lavel = 0;


	// 플레이어가 삭제한 라인 수입니다.
	int32_t RemoveLine = 0;


	// 플레이어의 남은 시간입니다. 단위는 초단위입니다.
	float RemainTime = 0.0f;


	// 플레이어가 현재 대기중인지 확인합니다.
	bool bIsWait = false;


	// 플레이어가 대기한 시간입니다.
	float WaitTime = 0.0f;
};