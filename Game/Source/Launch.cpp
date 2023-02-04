#include "GameEngine.h"
#include "Button.h"
#include "GraphicsManager.h"
#include "Label.h"
#include "InputManager.h"
#include "Shader.h"
#include "Timer.h"
#include "Window.h"
#include "WorldManager.h"

#include "Background.h"
#include "StartScene.h"
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
		StartScene_.reset();
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

		StartScene_ = std::make_unique<StartScene>();
		StartScene_->AddSwitchEvent(
			"START",
			[&]() {
				PlayScene_->Reset();
				CurrentGameScene_ = PlayScene_.get();
			}
		);
		StartScene_->AddSwitchEvent(
			"QUIT",
			[&]() {
				bIsDone_ = true;
			}
		);

		PlayScene_ = std::make_unique<PlayScene>();

		CurrentGameScene_ = StartScene_.get();
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
		std::function<void()> InactiveEvent = [&]() { };
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
	 * @brief 테트리스 게임의 시작 씬입니다.
	 */
	std::unique_ptr<StartScene> StartScene_ = nullptr;


	/**
	 * @brief 테트리스 게임의 플레이 씬입니다.
	 */
	std::unique_ptr<PlayScene> PlayScene_ = nullptr;
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