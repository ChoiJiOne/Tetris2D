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

		Camera_ = std::make_unique<Camera2D>(Vec2f(0.0f, 0.0f), 1000.0f, 800.0f);
		TileMap_ = std::make_unique<TileMap>("TileMap", Vec2f(0.0f, 0.0f), 20, 20, 30);

		Tile tile;

		for (int32_t Row = 0; Row < TileMap_->GetRowSize(); ++Row)
		{
			if (Row == 0 || Row == TileMap_->GetRowSize() - 1)
			{
				for (int32_t Col = 0; Col < TileMap_->GetColSize(); ++Col)
				{
					tile.SetPositionInMap(Vec2i(Col, Row));
					tile.SetState(Tile::EState::WALL);
					tile.SetColor(Tile::EColor::GRAY);
					TileMap_->WriteTileInMap(tile);
				}
			}
			else
			{
				tile.SetPositionInMap(Vec2i(0, Row));
				tile.SetState(Tile::EState::WALL);
				tile.SetColor(Tile::EColor::GRAY);
				TileMap_->WriteTileInMap(tile);

				tile.SetPositionInMap(Vec2i(TileMap_->GetColSize() - 1, Row));
				tile.SetState(Tile::EState::WALL);
				tile.SetColor(Tile::EColor::GRAY);
				TileMap_->WriteTileInMap(tile);
			}
		}
	}


	/**
	 * @brief 테트리스 게임의 가상 소멸자입니다.
	 */
	virtual ~Tetris()
	{
		TileMap_.reset();
		Camera_.reset();
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

			float Width = 0.0f, Height = 0.0f;
			Window_->GetSize<float>(Width, Height);
			GraphicsManager::Get().DrawTexture2D(ContentManager::Get().GetTexture2D("Background"), Vec2f(0.0f, 0.0f), Width, Height);

			TileMap_->Update(Timer_.GetDeltaTime());
			TileMap_->Render(*Camera_);

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
	 * @brief 게임 카메라입니다.
	 */
	std::unique_ptr<Camera2D> Camera_ = nullptr;


	/**
	 * @brief 2D 타일맵입니다.
	 */
	std::unique_ptr<TileMap> TileMap_ = nullptr;
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