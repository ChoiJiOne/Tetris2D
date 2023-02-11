#include "PlayScene.h"
#include "Background.h"
#include "Board.h"
#include "Button.h"
#include "GameObject.h"
#include "Label.h"
#include "InputManager.h"
#include "Tetromino.h"
#include "WorldManager.h"

PlayScene::PlayScene()
{
	BoardPosition_ = Vec2f(-180.0f, 330.0f);
	StartPosition_ = Vec2f(-60.0f, 300.0f);
	WaitPosition_ = Vec2f(230.0f, 300.0f);

	PauseEvent_ = [&]() {
		bIsPlaying_ = false;
		reinterpret_cast<Background*>(BasicObjects_[0])->StopAudio();
	};

	GameOverEvent_ = [&]() {
		bIsPlaying_ = false;
		reinterpret_cast<Background*>(BasicObjects_[0])->StopAudio();
		RunSwitchEvent("GAMEOVER");
	};

	ConstructBasicObjects();
	ConstructPauseObjects();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update(float DeltaSeconds)
{
	if (bIsPlaying_)
	{
		for (auto& BasicObject : BasicObjects_)
		{
			BasicObject->Tick(DeltaSeconds);
		}

		for (auto& TetrominoObject : TetrominoObjects_)
		{
			TetrominoObject->Tick(DeltaSeconds);
		}

		BoardObject_->Tick(DeltaSeconds);

		Board* BoardObject = reinterpret_cast<Board*>(BoardObject_);
		Tetromino* TetrominoObject = WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_));

		if (BoardObject->GetState() == Board::EState::WAIT && TetrominoObject->GetState() == Tetromino::EState::DONE)
		{
			TetrominoObjects_.remove(TetrominoObject);
			WorldManager::Get().UnregisterObject(std::to_string(CurrentTetromino_++));

			TetrominoObjects_.push_back(WorldManager::Get().CreateGameObject<Tetromino>(std::to_string(CountOfTetromino_++), WaitPosition_, 30.0f, 1.0f));

			if (!WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->CanTeleport(StartPosition_))
			{
				WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->SetState(Tetromino::EState::DONE);
				GameOverEvent_();
			}
			else
			{
				WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->Teleport(StartPosition_);
				WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->SetState(Tetromino::EState::ACTIVE);
			}
		}
	}
	else
	{
		for (auto& PauseObject : PauseObjects_)
		{
			PauseObject->Tick(DeltaSeconds);
		}
	}
}

void PlayScene::Reset()
{
	bIsPlaying_ = true;

	reinterpret_cast<Background*>(BasicObjects_[0])->ResetAudio();
	reinterpret_cast<Background*>(BasicObjects_[0])->PlayAudio();

	TetrominoObjects_.clear();
	if (WorldManager::Get().IsRegisterObject("BOARD::PlayScene"))
	{
		WorldManager::Get().UnregisterObject("BOARD::PlayScene");
	}

	if (CountOfTetromino_ != 0)
	{
		while (CurrentTetromino_ < CountOfTetromino_)
		{
			WorldManager::Get().UnregisterObject(std::to_string(CurrentTetromino_++));
		}
		
		CurrentTetromino_ = 0;
		CountOfTetromino_ = 0;
	}

	BoardObject_ = WorldManager::Get().CreateGameObject<Board>("BOARD::PlayScene", BoardPosition_, 22, 12, 30.0f, BoardUpdateStep_);

	TetrominoObjects_ = {
		WorldManager::Get().CreateGameObject<Tetromino>(std::to_string(CountOfTetromino_++), StartPosition_, 30.0f, TetrominoUpdateStep_),
		WorldManager::Get().CreateGameObject<Tetromino>(std::to_string(CountOfTetromino_++), WaitPosition_, 30.0f, TetrominoUpdateStep_),
	};

	WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->SetState(Tetromino::EState::ACTIVE);
}

void PlayScene::EnforcePause()
{
	bIsPlaying_ = false;

	if (PauseEvent_) PauseEvent_();
}

void PlayScene::ConstructBasicObjects()
{
	WorldManager& GWorld = WorldManager::Get();

	auto PlayEvent = [&]() {
		reinterpret_cast<Background*>(BasicObjects_[0])->PlayAudio();
	};

	auto StopEvent = [&]() {
		reinterpret_cast<Background*>(BasicObjects_[0])->StopAudio();
	};

	auto ResetEvent = [&]() {
		reinterpret_cast<Background*>(BasicObjects_[0])->ResetAudio();
	};

	auto VolubleEvent = [&]() {
		reinterpret_cast<Background*>(BasicObjects_[0])->Voluble();
	};

	auto MuteEvent = [&]() {
		reinterpret_cast<Background*>(BasicObjects_[0])->Mute();
	};

	BasicObjects_ = {
		GWorld.CreateGameObject<Background>("BACKGROUND::PlayScene", "Background", "Play", true),

		GWorld.CreateGameObject<Button>("ESC::PlayScene", Vec2f(-430.0f, +250.0f), 70.0f, 70.0f, "Box", L"ESC", MAGENTA, "Font32", EKeyCode::CODE_ESCAPE, PauseEvent_, 0.9f, false),
		GWorld.CreateGameObject<Button>("LEFT::PlayScene", Vec2f(-430.0f, +170.0f), 70.0f, 70.0f, "Left", EKeyCode::CODE_LEFT, nullptr, 0.9f, false),
		GWorld.CreateGameObject<Button>("DOWN::PlayScene", Vec2f(-350.0f, +170.0f), 70.0f, 70.0f, "Down", EKeyCode::CODE_DOWN, nullptr, 0.9f, false),
		GWorld.CreateGameObject<Button>("UP::PlayScene", Vec2f(-350.0f, +250.0f), 70.0f, 70.0f, "Up", EKeyCode::CODE_UP, nullptr, 0.9f, false),
		GWorld.CreateGameObject<Button>("RIGHT::PlayScene", Vec2f(-270.0f, +170.0f), 70.0f, 70.0f, "Right", EKeyCode::CODE_RIGHT, nullptr, 0.9f, false),
		GWorld.CreateGameObject<Button>("SPACE::PlayScene", Vec2f(-350.0f, +90.0f), 230.0f, 70.0f, "Button", L"SPACE", MAGENTA, "Font32", EKeyCode::CODE_SPACE, nullptr, 0.9f, false),

		GWorld.CreateGameObject<Button>("PLAY::PlayScene", Vec2f(-430.0f, +10.0f), 70.0f, 70.0f, "Play", EKeyCode::CODE_LBUTTON, PlayEvent, 0.9f),
		GWorld.CreateGameObject<Button>("STOP::PlayScene", Vec2f(-350.0f, +10.0f), 70.0f, 70.0f, "Stop", EKeyCode::CODE_LBUTTON, StopEvent, 0.9f),
		GWorld.CreateGameObject<Button>("PLAYBACK::PlayScene", Vec2f(-270.0f, +10.0f), 70.0f, 70.0f, "Reset", EKeyCode::CODE_LBUTTON, ResetEvent, 0.9f),

		GWorld.CreateGameObject<Button>("VOLUABLE::PlayScene", Vec2f(-390.0f, -70.0f), 70.0f, 70.0f, "Voluble", EKeyCode::CODE_LBUTTON, VolubleEvent, 0.9f),
		GWorld.CreateGameObject<Button>("MUTE::PlayScene", Vec2f(-310.0f, -70.0f), 70.0f, 70.0f, "Mute", EKeyCode::CODE_LBUTTON, MuteEvent, 0.9f),

		GWorld.CreateGameObject<Label>("NEXT::PlayScene", L"NEXT", "Font32", Vec2f(250.0f, 330.0f), MAGENTA),
	};
}

void PlayScene::ConstructPauseObjects()
{
	WorldManager& GWorld = WorldManager::Get();

	auto ContinueEvent = [&]() {
		reinterpret_cast<Background*>(BasicObjects_[0])->PlayAudio();
		bIsPlaying_ = true;
	};

	auto ResetEvent = [&]() {
		Reset();
	};

	auto QuitEvent = [&]() {
		RunSwitchEvent("QUIT");
	};

	PauseObjects_ = {
		GWorld.GetGameObject<Background>("BACKGROUND::PlayScene"),

		GWorld.CreateGameObject<Label>(
			"TITLE::PlayScene",
			L"TETRIS 2D",
			"Font128",
			Vec2f(0.0f, 200.f),
			MAGENTA
		),

		GWorld.CreateGameObject<Button>(
			"CONTINUE::PlayScene",
			Vec2f(0.0f, 0.0f),
			400.0f,
			100.0f,
			"Button",
			L"CONTINUE",
			MAGENTA,
			"Font64",
			EKeyCode::CODE_LBUTTON,
			ContinueEvent,
			0.9f,
			true
		),

		GWorld.CreateGameObject<Button>(
			"RESET::PlayScene",
			Vec2f(0.0f, -150.0f),
			400.0f,
			100.0f,
			"Button",
			L"RESET",
			MAGENTA,
			"Font64",
			EKeyCode::CODE_LBUTTON,
			ResetEvent,
			0.9f,
			true
		),

		GWorld.CreateGameObject<Button>(
			"QUIT::PlayScene",
			Vec2f(0.0f, -300.0f),
			400.0f,
			100.0f,
			"Button",
			L"QUIT",
			MAGENTA,
			"Font64",
			EKeyCode::CODE_LBUTTON,
			QuitEvent,
			0.9f,
			true
		),
	};
}
