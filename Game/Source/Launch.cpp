#include "Background.h"
#include "Button.h"
#include "Color.h"
#include "GameEngine.h"
#include "GraphicsManager.h"
#include "GameText.h"
#include "InputManager.h"
#include "Shader.h"
#include "Timer.h"
#include "Window.h"
#include "WorldManager.h"

#include "StartScene.h"
#include "DoneScene.h"
#include "SettingScene.h"
#include "PlayScene.h"
#include "PauseScene.h"


/**
 * @brief ��Ʈ���� ������ �ʱ�ȭ �� �����մϴ�./
 */
class Tetris : public GameEngine
{
public:
	/**
	 * @brief ��Ʈ���� ������ ����Ʈ �������Դϴ�.
	 */
	Tetris() = default;


	/**
	 * @brief ��Ʈ���� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Tetris()
	{
		for (auto& GameScene : Scenes_)
		{
			GameScene.second.reset();
		}
	}


	/**
	 * @brief ��Ʈ���� ������ �ʱ�ȭ�մϴ�.
	 * 
	 * @throws ��Ʈ���� ���� �ʱ�ȭ�� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	virtual void Initialize() override
	{
		GameEngine::Initialize();

		RegisterWindowEvent();
		CreateBasicGameObjectAndCamera();
		CreateScenesAndSwitchEvents();

		CurrentScene_ = Scenes_["Start"].get();
	}


	/**
	 * @brief ��Ʈ���� ������ �����մϴ�.
	 * 
	 * @return �ٸ� ���α׷��� ������ �� �ִ� ���� �ڵ带 ��ȯ�մϴ�.
	 */
	virtual int32_t Run() override
	{
		Timer_.Reset();

		while (!bIsDone_)
		{
			Timer_.Tick();
			InputManager::Get().Tick();

			GraphicsManager::Get().Clear(BLACK);

			CurrentScene_->Tick(Timer_.GetDeltaTime());

			GraphicsManager::Get().Present();
		}

		return 0;
	}


private:
	/**
	 * @brief ������ �̺�Ʈ�� ����մϴ�.
	 */
	void RegisterWindowEvent()
	{
		std::function<void()> CloseEvent = [&]() { bIsDone_ = true; };
		std::function<void()> InactiveEvent = [&]() { 
			PlayScene* PlayScenePtr = reinterpret_cast<PlayScene*>(Scenes_["Play"].get());
			if (CurrentScene_ == PlayScenePtr)
			{
				CurrentScene_ = Scenes_["Pause"].get();
			}
		};
		std::function<void()> ResizeEvent = [&]() {
			GraphicsManager::Get().Resize();
			float Width = 0.0f, Height = 0.0f;
			GraphicsManager::Get().GetBackBufferSize(Width, Height);
			WorldManager::Get().GetMainCamera().SetSize<float>(Width, Height);
		};

		const std::unordered_map<EWindowEvent, std::function<void()>> WindowEvents = {
			{ EWindowEvent::CLOSE,         CloseEvent},
			{ EWindowEvent::INACTIVE,      InactiveEvent},
			{ EWindowEvent::MINIMZED,      InactiveEvent},
			{ EWindowEvent::MAXIMIZED,     ResizeEvent},
			{ EWindowEvent::RESIZE,        ResizeEvent},
			{ EWindowEvent::ENTERSIZEMOVE, InactiveEvent},
		};

		for (const auto& WindowEvent : WindowEvents)
		{
			InputManager::Get().RegisterWindowEvent(WindowEvent.first, WindowEvent.second);
		}
	}


	/**
	 * @brief �⺻���� ���� ������Ʈ�� ī�޶� �����մϴ�.
	 */
	void CreateBasicGameObjectAndCamera()
	{
		float Width = 0.0f, Height = 0.0f;
		GraphicsManager::Get().GetBackBufferSize(Width, Height);
		WorldManager::Get().CreateMainCamera(Vec2f(0.0f, 0.0f), Width, Height);

		WorldManager::Get().CreateGameObject<GameText>("Title", L"TETRIS 2D", "Font128", Vec2f(0.0f, 250.0f), CYAN);
		WorldManager::Get().CreateGameObject<Background>("Background");
	}


	/**
	 * @brief ���� ���� ���� �̺�Ʈ�� �����մϴ�.
	 */
	void CreateScenesAndSwitchEvents()
	{
		std::function<void()> StartSceneSwitchEvent = [&]() {
			StartScene* StartScenePtr = reinterpret_cast<StartScene*>(Scenes_["Start"].get());
			StartScene::EState State = StartScenePtr->GetCurrentState();

			switch (State)
			{
			case StartScene::EState::START:
				CurrentScene_ = Scenes_["Play"].get();
				reinterpret_cast<PlayScene*>(CurrentScene_)->Reset();
				break;

			case StartScene::EState::SETTING:
				CurrentScene_ = Scenes_["Setting"].get();
				break;

			case StartScene::EState::QUIT:
				bIsDone_ = true;
				break;
			}
		};

		std::function<void()> SettingSceneSwitchEvent = [&]() {
			SettingScene* SettingScenePtr = reinterpret_cast<SettingScene*>(Scenes_["Setting"].get());
			SettingScene::EState State = SettingScenePtr->GetCurrentState();

			switch (State)
			{
			case SettingScene::EState::BACK:
				CurrentScene_ = Scenes_["Start"].get();
			}
		};

		std::function<void()> PlaySceneSwitchEvent = [&]() {
			PlayScene* PlayScenePtr = reinterpret_cast<PlayScene*>(Scenes_["Play"].get());
			PlayScene::EState State = PlayScenePtr->GetCurrentState();

			switch (State)
			{
			case PlayScene::EState::PAUSE:
				CurrentScene_ = Scenes_["Pause"].get();
				break;

			case PlayScene::EState::DONE:
				CurrentScene_ = Scenes_["Done"].get();
				break;
			}
		};

		std::function<void()> PauseSceneSwitchEvent = [&]() {
			PauseScene* PauseScenePtr = reinterpret_cast<PauseScene*>(Scenes_["Pause"].get());
			PauseScene::ESelectState SelectState = PauseScenePtr->GetSelectState();

			switch (SelectState)
			{
			case PauseScene::ESelectState::CONTINUE:
				CurrentScene_ = Scenes_["Play"].get();
				break;

			case PauseScene::ESelectState::RESET:
				CurrentScene_ = Scenes_["Start"].get();
				break;

			case PauseScene::ESelectState::QUIT:
				bIsDone_ = true;
				break;
			}
		};

		std::function<void()> DoneSceneSwitchEvent = [&]() {
			DoneScene* DoneScenePtr = reinterpret_cast<DoneScene*>(Scenes_["Done"].get());
			DoneScene::ESelectState SelectState = DoneScenePtr->GetSelectState();

			switch (SelectState)
			{
			case DoneScene::ESelectState::REPLAY:
				CurrentScene_ = Scenes_["Play"].get();
				reinterpret_cast<PlayScene*>(CurrentScene_)->Reset();
				break;

			case DoneScene::ESelectState::RESET:
				CurrentScene_ = Scenes_["Start"].get();
				break;

			case DoneScene::ESelectState::QUIT:
				bIsDone_ = true;
				break;
			}
		};

		Scenes_["Start"] = std::make_unique<StartScene>();
		Scenes_["Start"]->SetSwitchEvent(StartSceneSwitchEvent);

		Scenes_["Setting"] = std::make_unique<SettingScene>();
		Scenes_["Setting"]->SetSwitchEvent(SettingSceneSwitchEvent);

		Scenes_["Play"] =  std::make_unique<PlayScene>();
		Scenes_["Play"]->SetSwitchEvent(PlaySceneSwitchEvent);

		Scenes_["Pause"] = std::make_unique<PauseScene>();
		Scenes_["Pause"]->SetSwitchEvent(PauseSceneSwitchEvent);

		Scenes_["Done"] =  std::make_unique<DoneScene>();
		Scenes_["Done"]->SetSwitchEvent(DoneSceneSwitchEvent);
	}


private:
	/**
	 * @brief ���� Ÿ�̸��Դϴ�.
	 */
	Timer Timer_;


	/**
	 * @brief ���� ���� ���� ���Դϴ�.
	 */
	Scene* CurrentScene_ = nullptr;


	/**
	 * @brief ��Ʈ���� ���� ���� ���Դϴ�.
	 */
	std::unordered_map<std::string, std::unique_ptr<Scene>> Scenes_;
};


/**
 * @brief Windows ���ø����̼� �������Դϴ�.
 * 
 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/winmain--the-application-entry-point
 * 
 * @param hInstance �ν��Ͻ��� ���� �ڵ��Դϴ�.
 * @param hPrevInstance �ƹ� �ǹ� ���� �Ķ�����Դϴ�.
 * @param CmdLine ������ �μ��Դϴ�.
 * @param CmdShow �⺻ ���ø����̼� â�� �ּ�ȭ����, �ִ�ȭ���� �Ǵ� ���������� ǥ�������� ��Ÿ���� �÷����Դϴ�.
 * 
 * @return �ٸ� ���α׷��� ������ �� �ִ� ���� �ڵ带 ��ȯ�մϴ�.
 */
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR CmdLine, int32_t CmdShow)
{
	auto Game = std::make_unique<Tetris>();
	Game->Initialize();
	return Game->Run();
}