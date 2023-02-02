#include "DoneScene.h"
#include "Background.h"
#include "Button.h"
#include "ContentManager.h"
#include "GraphicsManager.h"
#include "GameText.h"
#include "Shader.h"
#include "Texture2D.h"
#include "WorldManager.h"

DoneScene::DoneScene()
{
	WorldManager& GWorld = WorldManager::Get();

	std::function<void()> ReplayEvent = [&]() {
		CurrentState_ = EState::REPLAY;
		RunSwitchEvent();
	};

	std::function<void()> ResetEvent = [&]() {
		CurrentState_ = EState::RESET;
		RunSwitchEvent();
	};

	std::function<void()> QuitEvent = [&]() {
		CurrentState_ = EState::QUIT;
		RunSwitchEvent();
	};

	std::string TextureSignature = "Button";
	std::string FontSignature = "Font32";
	Vec2f Positon = Vec2f(0.0f, 100.0f);
	float Width = 300.0f;
	float Height = 50.0f;
	float ReduceRate = 0.9f;
	LinearColor Color = MAGENTA;
	float Gap = 100.0f;

	SceneButton_ = {
		GWorld.CreateGameObject<Button>(
			"Replay::DoneScene",
			Vec2f(Positon.x, Positon.y),
			Width,
			Height,
			TextureSignature,
			L"REPLAY",
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			ReplayEvent,
			ReduceRate
		),

		GWorld.CreateGameObject<Button>(
			"Reset::DoneScene",
			Vec2f(Positon.x, Positon.y - Gap),
			Width,
			Height,
			TextureSignature,
			L"RESET",
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			ResetEvent,
			ReduceRate
		),

		WorldManager::Get().CreateGameObject<Button>(
			"Quit::DoneScene",
			Vec2f(Positon.x, Positon.y - 2.0f * Gap),
			Width,
			Height,
			TextureSignature,
			L"QUIT",
			Color,
			FontSignature,
			EKeyCode::CODE_LBUTTON,
			QuitEvent,
			ReduceRate
		)
	};
}

DoneScene::~DoneScene()
{
}

void DoneScene::Tick(float DeltaSeconds)
{
	WorldManager::Get().GetGameObject<Background>("Background")->Tick(DeltaSeconds);
	WorldManager::Get().GetGameObject<GameText>("Title")->Tick(DeltaSeconds);

	GameScene::Tick(DeltaSeconds);
}
