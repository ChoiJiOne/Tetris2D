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
 * @brief 테트리스 게임을 초기화 및 실행합니다./
 */
class Tetris : public GameEngine
{
public:
	/**
	 * @brief 테트리스 게임의 디폴트 생성자입니다.
	 */
	Tetris() = default;


	/**
	 * @brief 테트리스 게임의 가상 소멸자입니다.
	 */
	virtual ~Tetris()
	{
		for (auto& GameScene : Scenes_)
		{
			GameScene.second.reset();
		}
	}


	/**
	 * @brief 테트리스 게임을 초기화합니다.
	 * 
	 * @throws 테트리스 게임 초기화에 실패하면 C++ 표준 예외를 던집니다.
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
	 * @brief 테트리스 게임을 실행합니다.
	 * 
	 * @return 다른 프로그램에 전달할 수 있는 상태 코드를 반환합니다.
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
	 * @brief 윈도우 이벤트를 등록합니다.
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
	 * @brief 기본적인 게임 오브젝트와 카메라를 생성합니다.
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
	 * @brief 게임 내의 씬과 이벤트를 생성합니다.
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
	 * @brief 게임 타이머입니다.
	 */
	Timer Timer_;


	/**
	 * @brief 현재 실행 중인 씬입니다.
	 */
	Scene* CurrentScene_ = nullptr;


	/**
	 * @brief 테트리스 게임 내의 씬입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<Scene>> Scenes_;
};


/**
 * @brief Windows 애플리케이션 진입점입니다.
 * 
 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/winmain--the-application-entry-point
 * 
 * @param hInstance 인스턴스에 대한 핸들입니다.
 * @param hPrevInstance 아무 의미 없는 파라미터입니다.
 * @param CmdLine 명령줄 인수입니다.
 * @param CmdShow 기본 애플리케이션 창을 최소화할지, 최대화할지 또는 정상적으로 표시할지를 나타내는 플래그입니다.
 * 
 * @return 다른 프로그램에 전달할 수 있는 상태 코드를 반환합니다.
 */
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR CmdLine, int32_t CmdShow)
{
	auto Game = std::make_unique<Tetris>();
	Game->Initialize();
	return Game->Run();
}