#include "GameEngine.h"
#include "Button.h"
#include "ErrorHandler.h"
#include "GraphicsManager.h"
#include "Label.h"
#include "InputManager.h"
#include "Shader.h"
#include "Timer.h"
#include "Window.h"
#include "WorldManager.h"

#include "Background.h"
#include "GameOverScene.h"
#include "TitleScene.h"
#include "PlayScene.h"


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
		GameOverScene_.reset();
		PlayScene_.reset();
		TitleScene_.reset();
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

		float Width = 0.0f, Height = 0.0f;
		GraphicsManager::Get().GetBackBufferSize(Width, Height);
		WorldManager::Get().CreateMainCamera(Vec2f(0.0f, 0.0f), Width, Height);

		auto QuitEvent = [&]() { bIsDone_ = true; };
		auto ResetPlaySceneEvent = [&]() {
			CurrentGameScene_ = PlayScene_.get();
			CurrentGameScene_->Reset();
		};
		auto GameOverEvent = [&]() {
			CurrentGameScene_ = GameOverScene_.get();

			GameOverScene_->SetUserInfo(PlayScene_->GetUserPlayTime(), PlayScene_->GetUserRemoveLine(), PlayScene_->GetUserLevel());
			CurrentGameScene_->Reset();
		};

		TitleScene_ = std::make_unique<TitleScene>();
		TitleScene_->AddSwitchEvent("START", ResetPlaySceneEvent);
		TitleScene_->AddSwitchEvent("QUIT", QuitEvent);

		PlayScene_ = std::make_unique<PlayScene>();
		PlayScene_->AddSwitchEvent("GAMEOVER", GameOverEvent);
		PlayScene_->AddSwitchEvent("QUIT", QuitEvent);

		GameOverScene_ = std::make_unique<GameOverScene>();
		GameOverScene_->AddSwitchEvent("REPLAY", ResetPlaySceneEvent);
		GameOverScene_->AddSwitchEvent("QUIT", QuitEvent);

		CurrentGameScene_ = TitleScene_.get();
		CurrentGameScene_->Reset();
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

			CurrentGameScene_->Update(Timer_.GetDeltaTime());

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
			if (CurrentGameScene_ == PlayScene_.get())
			{
				reinterpret_cast<PlayScene*>(CurrentGameScene_)->EnforcePause();
			}
		};
		std::function<void()> ResizeEvent = [&]() {
			GraphicsManager::Get().Resize();
			float Width = 0.0f, Height = 0.0f;
			GraphicsManager::Get().GetBackBufferSize(Width, Height);
			WorldManager::Get().GetMainCamera().SetSize<float>(Width, Height);

			if (CurrentGameScene_ == PlayScene_.get())
			{
				reinterpret_cast<PlayScene*>(CurrentGameScene_)->EnforcePause();
			}
		};

		const std::unordered_map<EWindowEvent, std::function<void()>> WindowEvents = {
			{ EWindowEvent::CLOSE,         CloseEvent    },
			{ EWindowEvent::INACTIVE,      InactiveEvent },
			{ EWindowEvent::MINIMZED,      InactiveEvent },
			{ EWindowEvent::MAXIMIZED,     ResizeEvent   },
			{ EWindowEvent::RESIZE,        ResizeEvent   },
			{ EWindowEvent::ENTERSIZEMOVE, InactiveEvent },
		};

		for (const auto& WindowEvent : WindowEvents)
		{
			InputManager::Get().BindWindowEvent(WindowEvent.first, WindowEvent.second);
		}
	}


private:
	/**
	 * @brief 게임 타이머입니다.
	 */
	Timer Timer_;

	
	/**
	 * @brief 현재 게임 씬입니다.
	 */
	Scene* CurrentGameScene_ = nullptr;


	/**
	 * @brief 테트리스 게임의 타이틀 씬입니다.
	 */
	std::unique_ptr<TitleScene> TitleScene_ = nullptr;


	/**
	 * @brief 테트리스 게임의 플레이 씬입니다.
	 */
	std::unique_ptr<PlayScene> PlayScene_ = nullptr;


	/**
	 * @brief 테트리스 게임의 종료 씬입니다.
	 */
	std::unique_ptr<GameOverScene> GameOverScene_ = nullptr;
};


/**
 * @brief 애플케이션을 실행합니다.
 * 
 * @throws 애플리케이션 실행 중 에러 발생 시 예외를 던집니다.
 */
void RunApplication()
{
	auto Game = std::make_unique<Tetris>();
	Game->Initialize();
	Game->Run();
}


/**
 * @brief 애플리케이션의 진입점입니다.
 *
 * @param Argc 명령행 인자의 수입니다.
 * @param Argv 명령행 인자입니다.
 *
 * @return 다른 프로그램에 전달할 수 있는 상태 코드를 반환합니다.
 */
int32_t main(int32_t Argc, char** Argv)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	__try
	{
		RunApplication();
	}
	__except (ErrorHandler::GenerateCrashDump(GetExceptionInformation()))
	{
		ErrorHandler::ShowErrorMessageBox();
	}

	return 0;
}