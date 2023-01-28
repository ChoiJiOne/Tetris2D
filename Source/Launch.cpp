#include "Background.h"
#include "Camera2D.h"
#include "CommandLineManager.h"
#include "ContentManager.h"
#include "Config.h"
#include "Color.h"
#include "Debug.h"
#include "Font.h"
#include "GameEngine.h"
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
#include "WorldManager.h"

#include "Board.h"
#include "Tetromino.h"
#include "TileMap.h"


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

		StartPosition_ = Vec2i(10, 1);
		WaitPosition_ = Vec2i(19, 2);

		WorldManager::Get().CreateMainCamera(Vec2f(0.0f, 0.0f), 1000.0f, 800.0f);
		WorldManager::Get().CreateGameObject<TileMap>("TileMap", Vec2f(0.0f, 0.0f), 22, 24, 30);
		WorldManager::Get().CreateGameObject<Background>("Background");

		WorldManager::Get().CreateGameObject<Board>("Board", Vec2i(6, 0), 12, 22);
		WorldManager::Get().CreateGameObject<Tetromino>(std::to_string(CountOfTetromino_++), StartPosition_);
		WorldManager::Get().CreateGameObject<Tetromino>(std::to_string(CountOfTetromino_++), WaitPosition_);

		WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->SetState(Tetromino::EState::ACTIVE);
	}


	/**
	 * @brief 테트리스 게임의 가상 소멸자입니다.
	 */
	virtual ~Tetris()
	{
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

			if (InputManager::Get().GetKeyPressState(EKeyCode::CODE_ESCAPE) == EPressState::PRESSED)
			{
				bIsDone_ = true;
			}

			GraphicsManager::Get().Clear(BLACK);

			WorldManager::Get().GetGameObject<Background>("Background")->Tick(Timer_.GetDeltaTime());
			WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->Tick(Timer_.GetDeltaTime());
			WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_ + 1))->Tick(Timer_.GetDeltaTime());
			WorldManager::Get().GetGameObject<Board>("Board")->Tick(Timer_.GetDeltaTime());
			WorldManager::Get().GetGameObject<TileMap>("TileMap")->Tick(Timer_.GetDeltaTime());

			if (WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->GetState() == Tetromino::EState::DONE)
			{
				if (WorldManager::Get().GetGameObject<Board>("Board")->GetState() == Board::EState::ACTIVE)
				{
					WorldManager::Get().GetGameObject<Board>("Board")->SetState(Board::EState::WAIT);
				}
				else
				{
					WorldManager::Get().UnregisterObject(std::to_string(CurrentTetromino_++));

					WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->SetState(Tetromino::EState::ACTIVE);
					if (!WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->CanTeleport(StartPosition_))
					{
						bIsDone_ = true;
					}

					WorldManager::Get().GetGameObject<Tetromino>(std::to_string(CurrentTetromino_))->Teleport(StartPosition_);
					WorldManager::Get().CreateGameObject<Tetromino>(std::to_string(CountOfTetromino_++), WaitPosition_);
				}
			}

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
	 * @brief 테트로미노의 시작 위치입니다.
	 */
	Vec2i StartPosition_;


	/**
	 * @brief 테트로미노의 대기 위치입니다.
	 */
	Vec2i WaitPosition_;


	/**
	 * @brief 생성된 테트로미노 수입니다.
	 */
	int32_t CountOfTetromino_ = 0;


	/**
	 * @brief 현재 테트로미노의 번호입니다.
	 */
	int32_t CurrentTetromino_ = 0;
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