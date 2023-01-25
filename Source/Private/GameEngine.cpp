#include "GameEngine.h"
#include "ContentManager.h"
#include "Config.h"
#include "Debug.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Window.h"

GameEngine::GameEngine()
{
	SetUnhandledExceptionFilter(UnhandledExceptionHandler);

	CreateWindowFromConfig();
	GraphicsManager::Get().Init(Window_.get());
}

GameEngine::~GameEngine()
{
	GraphicsManager::Get().Cleanup();
	Window_.reset();
}

void GameEngine::CreateWindowFromConfig()
{
	Config& WindowConfig = ContentManager::Get().LoadConfig("Window", "Window.config");

	WindowConstructorParam Param;

	Param.Title = Convert(WindowConfig.GetValue("Title"));
	Param.PositionX = std::stoi(WindowConfig.GetValue("x"));
	Param.PositionY = std::stoi(WindowConfig.GetValue("y"));
	Param.Width = std::stoi(WindowConfig.GetValue("Width"));
	Param.Height = std::stoi(WindowConfig.GetValue("Height"));
	Param.bIsFullScreen = std::stoi(WindowConfig.GetValue("FullScreen")) ? true : false;

	Window_ = std::make_unique<Window>(Param);
}
