#include "Background.h"
#include "Button.h"
#include "Color.h"
#include "GameEngine.h"
#include "GraphicsManager.h"
#include "GameTitle.h"
#include "InputManager.h"
#include "Shader.h"
#include "Timer.h"
#include "WorldManager.h"

#include "StartScene.h"
#include "PlayScene.h"



/**
 * @brief 테트리스 게임을 초기화 및 실행합니다.
 */
class Tetris : public GameEngine
{
public:
	/**
	 * @brief 테트리스 게임의 생성자입니다.
	 * 
	 * @throws 
	 * 초기화에 실패하면 C++ 표준 예외를 던집니다.
	 */
	Tetris()
	{
		InputManager::Get().RegisterWindowEvent(
			EWindowEvent::CLOSE,
			[&]() {
				bIsDone_ = true;
			}
		);

		InputManager::Get().RegisterWindowEvent(
			EWindowEvent::RESIZE,
			[&]() {
				GraphicsManager::Get().Resize();

				float Width = 0.0f, Height = 0.0f;
				GraphicsManager::Get().GetBackBufferSize(Width, Height);
				WorldManager::Get().GetMainCamera().SetSize<float>(Width, Height);
			}
		);

		InputManager::Get().RegisterWindowEvent(
			EWindowEvent::MAXIMIZED,
			[&]() {
				GraphicsManager::Get().Resize();

				float Width = 0.0f, Height = 0.0f;
				GraphicsManager::Get().GetBackBufferSize(Width, Height);
				WorldManager::Get().GetMainCamera().SetSize<float>(Width, Height);
			}
		);

		GraphicsManager::Get().SetDepthBuffer(false);
		GraphicsManager::Get().SetAlphaBlend(true);
		GraphicsManager::Get().SetFillMode(true);
		
		WorldManager::Get().CreateMainCamera(Vec2f(0.0f, 0.0f), 1000.0f, 800.0f);
		WorldManager::Get().CreateGameObject<GameTitle>("Title", L"TETRIS 2D", Vec2f(0.0f, 250.0f), CYAN);
		WorldManager::Get().CreateGameObject<Background>("Background");
		WorldManager::Get().CreateGameObject<Button>(
			"PlayButton", 
			Vec2f(0.0f, 0.0f), 
			80.0f, 
			80.0f, 
			"Play",
			EKeyCode::CODE_LBUTTON, 
			[&]() {
				CurrentScene = PlayScene_.get();
				PlayScene_->Reset();
			},
			0.9f
		);

		StartScene_ = std::make_unique<StartScene>();
		StartScene_->SetSwitchEvent(
			[&]() {
				CurrentScene = PlayScene_.get();
				PlayScene_->Reset();
			}
		);

		PlayScene_ = std::make_unique<PlayScene>();
		PlayScene_->SetSwitchEvent(
			[&]() {
				bIsDone_ = true;
			}
		);

		CurrentScene = StartScene_.get();
	}


	/**
	 * @brief 테트리스 게임의 가상 소멸자입니다.
	 */
	virtual ~Tetris()
	{
		PlayScene_.reset();
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

			CurrentScene->Tick(Timer_.GetDeltaTime());

			GraphicsManager::Get().Present();
		}

		return 0;
	}


private:
	/**
	 * @brief 게임 타이머입니다.
	 */
	Timer Timer_;


	/**
	 * @brief 현재 실행 중인 씬입니다.
	 */
	Scene* CurrentScene = nullptr;


	/**
	 * @brief 시작 씬입니다.
	 */
	std::unique_ptr<StartScene> StartScene_ = nullptr;

	
	/**
	 * @brief 플레이 씬입니다.
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
	return Game->Run();
}