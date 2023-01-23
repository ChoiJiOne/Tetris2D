#include "CommandLineManager.h"
#include "Color.h"
#include "Debug.h"
#include "Font.h"
#include "GameFramework.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "Macro.h"
#include "Math.hpp"
#include "Random.h"
#include "Texture2D.h"
#include "Timer.h"
#include "Vector.hpp"
#include "Window.h"

#include "Primitive2DRenderShader.h"
#include "Texture2DRenderShader.h"
#include "Text2DRenderShader.h"


/**
 * @brief 테트리스 게임을 초기화 및 실행합니다.
 */
class Tetris : public GameFramework
{
public:
	/**
	 * @brief 테트리스 게임의 기본 생성자입니다.
	 */
	Tetris() = default;


	/**
	 * @brief 테트리스 게임의 가상 소멸자입니다.
	 */
	virtual ~Tetris()
	{
		Font_.reset();
		Texture_.reset();

		GraphicsManager::Get().Cleanup();
		Window_.reset();
	}


	/**
	 * @brief 테트리스 게임을 초기화합니다.
	 */
	virtual void Init() override
	{
		SetUnhandledExceptionFilter(UnhandledExceptionHandler);

		Window_ = std::make_unique<Window>(
			WindowConstructorParam {
				L"Tetris2D", 200, 200, 1000, 800, false
			}
		);

		GraphicsManager::Get().Init(Window_.get());

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
			}
		);

		InputManager::Get().RegisterWindowEvent(
			EWindowEvent::MAXIMIZED,
			[&]() {
				GraphicsManager::Get().Resize();
			}
		);

		GraphicsManager::Get().SetDepthBuffer(false);
		GraphicsManager::Get().SetAlphaBlend(true);

		Texture_ = std::make_unique<Texture2D>(GraphicsManager::Get().GetDevice(), "D:\\work\\Tetris2D\\Content\\Texture\\Space.png");
		Font_ = std::make_unique<Font>(GraphicsManager::Get().GetDevice(), "D:\\work\\Tetris2D\\Content\\Font\\JetBrainsMono-Bold.ttf", 0x20, 0x7E, 32.0f);
 	}


	/**
	 * @brief 테트리스 게임을 실행합니다.
	 */
	virtual void Run() override
	{
		Timer_.Reset();

		while (!bIsDone_)
		{
			Timer_.Tick();
			InputManager::Get().Tick();

			if (InputManager::Get().GetKeyPressState(VK_ESCAPE) == EPressState::PRESSED)
			{
				bIsDone_ = true;
			}

			GraphicsManager::Get().Clear(BLACK);

			float Width = 0.0f, Height = 0.0f;
			Window_->GetSize<float>(Width, Height);
			GraphicsManager::Get().DrawTexture2D(*Texture_.get(), Vec2f(0.0f, 0.0f), Width, Height);
			GraphicsManager::Get().DrawText2D(*Font_.get(), L"Hello World", Vec2f(0.0f, 0.0f), MAGENTA);

			GraphicsManager::Get().Present();
		}
	}


private:
	/**
	 * @brief 게임 루프를 수행할 지 확인합니다.
	 */
	bool bIsDone_ = false;


	/**
	 * @brief 게임 타이머입니다.
	 */
	Timer Timer_;


	/**
	 * @brief 윈도우 창입니다.
	 */
	std::unique_ptr<Window> Window_ = nullptr;


	/**
	 * @brief 텍스처 리소스입니다.
	 */
	std::unique_ptr<Texture2D> Texture_ = nullptr;


	/**
	 * @brief 폰트 리소스입니다.
	 */
	std::unique_ptr<Font> Font_ = nullptr;
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
	Game->Init();
	Game->Run();

	return 0;
}