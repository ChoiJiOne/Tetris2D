#include "CommandLineManager.h"
#include "Debug.h"
#include "GameFramework.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "Macro.h"
#include "Random.h"
#include "Timer.h"
#include "Vector.hpp"
#include "Window.h"
#include "Primitive2DRenderShader.h"


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
		Primitive2DRenderShader_.reset();

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
				GraphicsManager::Get().SetScreenViewport();
			}
		);

		GraphicsManager::Get().SetScreenViewport();

		//DirectX::XMMatrixOrthographicRH()

		Primitive2DRenderShader_ = std::make_unique<Primitive2DRenderShader>(
			GraphicsManager::Get().GetDevice(),
			L"D:\\work\\Tetris2D\\Source\\Shader\\Primitive2DRenderVS.hlsl",
			L"D:\\work\\Tetris2D\\Source\\Shader\\Primitive2DRenderPS.hlsl"
		);
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

			float Delta = std::abs(std::sin(Timer_.GetTotalTime()));

			GraphicsManager::Get().Clear(0.0f, 0.0f, 0.0f, 1.0f);

			/*PrimitiveShader_->RenderPoint(
				GraphicsManager::Get().GetContext(),
				Vec3f(Delta, 0.0f, 0.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f)
			);

			PrimitiveShader_->RenderLine(
				GraphicsManager::Get().GetContext(),
				Vec3f(+Delta, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f),
				Vec3f(-Delta, 0.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f)
			);

			PrimitiveShader_->RenderWireframeTriangle(
				GraphicsManager::Get().GetContext(),
				Vec3f(-1.0f, -1.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f),
				Vec3f(+0.0f, +1.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f),
				Vec3f(+1.0f, -1.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f)
			);*/

			Primitive2DRenderShader_->RenderWireframeQuad(
				GraphicsManager::Get().GetContext(),
				Vec3f(-1.0f * Delta, -1.0f * Delta, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f),
				Vec3f(-1.0f * Delta, +1.0f * Delta, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f),
				Vec3f(+1.0f * Delta, +1.0f * Delta, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f),
				Vec3f(+1.0f * Delta, -1.0f * Delta, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f)
			);

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
	 * @brief 기본 도형을 렌더링 하기 위한 셰이더입니다.
	 */
	std::unique_ptr<Primitive2DRenderShader> Primitive2DRenderShader_ = nullptr;
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