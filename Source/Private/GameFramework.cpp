#include "GameFramework.h"
#include "ContentManager.h"
#include "Config.h"
#include "Debug.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Window.h"

GameFramework::GameFramework()
{
	SetUnhandledExceptionFilter(UnhandledExceptionHandler);

	CreateWindowFromConfig();
	GraphicsManager::Get().Init(Window_.get());
}

GameFramework::~GameFramework()
{
	GraphicsManager::Get().Cleanup();
	Window_.reset();
}

void GameFramework::CreateWindowFromConfig()
{
	Config& WindowConfig = ContentManager::Get().LoadConfig("Window", "Window.config");

	WindowConstructorParam Param;

	Param.Title = Convert(WindowConfig.GetValue("title"));
	Param.PositionX = std::stoi(WindowConfig.GetValue("x"));
	Param.PositionY = std::stoi(WindowConfig.GetValue("y"));
	Param.Width = std::stoi(WindowConfig.GetValue("width"));
	Param.Height = std::stoi(WindowConfig.GetValue("height"));
	Param.bIsFullScreen = std::stoi(WindowConfig.GetValue("fullscreen")) ? true : false;

	Window_ = std::make_unique<Window>(Param);
}
