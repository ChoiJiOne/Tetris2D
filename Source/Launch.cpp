#include "CommandLineManager.h"
#include "ContentManager.h"
#include "Config.h"
#include "Color.h"
#include "Debug.h"
#include "Font.h"
#include "GameFramework.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "Macro.h"
#include "Math.hpp"
#include "Random.h"
#include "Sound.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Timer.h"
#include "Vector.hpp"
#include "Window.h"


/**
 * @brief ��Ʈ���� ������ �ʱ�ȭ �� �����մϴ�.
 */
class Tetris : public GameFramework
{
public:
	/**
	 * @brief ��Ʈ���� ������ �������Դϴ�.
	 * 
	 * @throws 
	 * �ʱ�ȭ�� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
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
		GraphicsManager::Get().SetFillMode(true);

		ContentManager::Get().LoadTexture2D("Background", "Space.png");
		ContentManager::Get().LoadFont("Font32", "SeoulNamsanEB.ttf", 0x20, 0xD7A3, 32.0f);
	}


	/**
	 * @brief ��Ʈ���� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Tetris()
	{
	}


	/**
	 * @brief ��Ʈ���� ������ �����մϴ�.
	 */
	virtual void Run() override
	{
		Timer_.Reset();

		while (!bIsDone_)
		{
			Timer_.Tick();
			InputManager::Get().Tick();

			if (InputManager::Get().GetKeyPressState(EKeyCode::CODE_ESCAPE) == EPressState::PRESSED)
			{
				bIsDone_ = true;
			}

			GraphicsManager::Get().Clear(BLACK);

			float Width = 0.0f, Height = 0.0f;
			Window_->GetSize<float>(Width, Height);
			GraphicsManager::Get().DrawTexture2D(ContentManager::Get().GetTexture2D("Background"), Vec2f(0.0f, 0.0f), Width, Height);
			GraphicsManager::Get().DrawText2D(ContentManager::Get().GetFont("Font32"), L"�ѱ� ��� Ȯ��", Vec2f(0.0f, 0.0f), MAGENTA);

			GraphicsManager::Get().Present();
		}
	}


private:
	/**
	 * @brief ���� Ÿ�̸��Դϴ�.
	 */
	Timer Timer_;
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
	Game->Run();

	return 0;
}