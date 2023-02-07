#include "PlayScene.h"
#include "Background.h"
#include "Button.h"
#include "GameObject.h"
#include "Label.h"
#include "InputManager.h"
#include "WorldManager.h"

PlayScene::PlayScene()
{
	WorldManager& GWorld = WorldManager::Get();

	PauseEvent_ = [&]() {
		bIsPlaying = false;
		reinterpret_cast<Background*>(SceneObjects_[0])->InactiveAudio();
	};

	GameOverEvent_ = [&]() {
		bIsPlaying = false;
		reinterpret_cast<Background*>(SceneObjects_[0])->InactiveAudio();
		RunSwitchEvent("GAMEOVER");
	};

	auto PlayEvent = [&]() {
		reinterpret_cast<Background*>(SceneObjects_[0])->ActiveAudio();
	};

	auto StopEvent = [&]() {
		reinterpret_cast<Background*>(SceneObjects_[0])->InactiveAudio();
	};

	auto ResetEvent = [&]() {
		reinterpret_cast<Background*>(SceneObjects_[0])->ResetAudio();
	};

	auto VolubleEvent = [&]() {
		reinterpret_cast<Background*>(SceneObjects_[0])->Voluble();
	};

	auto MuteEvent = [&]() {
		reinterpret_cast<Background*>(SceneObjects_[0])->Mute();
	};

	SceneObjects_ = {
		GWorld.CreateGameObject<Background>("BACKGROUND::PlayScene", "Background", "Play", true),

		GWorld.CreateGameObject<Button>("ESC::PlayScene", Vec2f(-430.0f, +250.0f), 70.0f, 70.0f, "Box", L"ESC", MAGENTA, "Font32", EKeyCode::CODE_ESCAPE, GameOverEvent_, 0.9f, false),
		GWorld.CreateGameObject<Button>("LEFT::PlayScene", Vec2f(-430.0f, +170.0f), 70.0f, 70.0f, "Left", EKeyCode::CODE_LEFT, nullptr, 0.9f, false),
		GWorld.CreateGameObject<Button>("DOWN::PlayScene", Vec2f(-350.0f, +170.0f), 70.0f, 70.0f, "Down", EKeyCode::CODE_DOWN, nullptr, 0.9f, false),
		GWorld.CreateGameObject<Button>("UP::PlayScene", Vec2f(-350.0f, +250.0f), 70.0f, 70.0f, "Up", EKeyCode::CODE_UP, nullptr, 0.9f, false),
		GWorld.CreateGameObject<Button>("RIGHT::PlayScene", Vec2f(-270.0f, +170.0f), 70.0f, 70.0f, "Right", EKeyCode::CODE_RIGHT, nullptr, 0.9f, false),
		GWorld.CreateGameObject<Button>("SPACE::PlayScene", Vec2f(-350.0f, +90.0f), 230.0f, 70.0f, "Button", L"SPACE", MAGENTA, "Font32", EKeyCode::CODE_SPACE, nullptr, 0.9f, false),

		GWorld.CreateGameObject<Button>("PLAY::PlayScene", Vec2f(-430.0f, +10.0f), 70.0f, 70.0f, "Play", EKeyCode::CODE_LBUTTON, PlayEvent, 0.9f),
		GWorld.CreateGameObject<Button>("STOP::PlayScene", Vec2f(-350.0f, +10.0f), 70.0f, 70.0f, "Stop", EKeyCode::CODE_LBUTTON, StopEvent, 0.9f),
		GWorld.CreateGameObject<Button>("RESET::PlayScene", Vec2f(-270.0f, +10.0f), 70.0f, 70.0f, "Reset", EKeyCode::CODE_LBUTTON, ResetEvent, 0.9f),

		GWorld.CreateGameObject<Button>("VOLUABLE::PlayScene", Vec2f(-390.0f, -70.0f), 70.0f, 70.0f, "Voluble", EKeyCode::CODE_LBUTTON, VolubleEvent, 0.9f),
		GWorld.CreateGameObject<Button>("MUTE::PlayScene", Vec2f(-310.0f, -70.0f), 70.0f, 70.0f, "Mute", EKeyCode::CODE_LBUTTON, MuteEvent, 0.9f),

		GWorld.CreateGameObject<Label>("NEXT::PlayScene", L"NEXT", "Font32", Vec2f(250.0f, 330.0f), MAGENTA)
	};
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update(float DeltaSeconds)
{
	for (auto& SceneObject : SceneObjects_)
	{
		SceneObject->Tick(DeltaSeconds);
	}
}

void PlayScene::Reset()
{
	bIsPlaying = true;

	reinterpret_cast<Background*>(SceneObjects_[0])->ResetAudio();
	reinterpret_cast<Background*>(SceneObjects_[0])->ActiveAudio();
}

void PlayScene::EnforcePause()
{
	if (PauseEvent_) PauseEvent_();
}
