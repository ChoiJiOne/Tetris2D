#pragma once

#include <array>

#include "InputManager.h"

#include "IGameScene2D.h"

class GamePlayScene2D : public IGameScene2D
{
public:
	GamePlayScene2D();
	virtual ~GamePlayScene2D();

	DISALLOW_COPY_AND_ASSIGN(GamePlayScene2D);

	virtual void Tick(float deltaSeconds) override;
	virtual void Enter() override;
	virtual void Exit() override;

	void Reset();

private:
	std::array<WindowEventID, 3> windowEventIDs_;

	class TetrominoController* tetrominoController_ = nullptr;
};