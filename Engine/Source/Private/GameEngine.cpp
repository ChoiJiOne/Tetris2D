#include "GameEngine.h"
#include "ContentManager.h"
#include "Config.h"
#include "GraphicsManager.h"
#include "Shader.h"
#include "Text.hpp"
#include "Window.h"

GameEngine::~GameEngine()
{
	GraphicsManager::Get().Cleanup();
	Window_.reset();
}

void GameEngine::Initialize()
{
	CreateWindowFromConfig();
	GraphicsManager::Get().Setup(Window_.get());

	LoadFontFromConfig();
	LoadTextureFromConfig();
	LoadAudioFromConfig();

	// 2D Graphics Setting...
	GraphicsManager::Get().SetDepthBuffer(false);
	GraphicsManager::Get().SetAlphaBlend(true);
	GraphicsManager::Get().SetFillMode(true);
}

void GameEngine::CreateWindowFromConfig()
{
	Config& WindowConfig = ContentManager::Get().LoadConfig("Window", "Window.config");

	const std::vector<std::string>& Position = Split(WindowConfig.GetValue("Position"), ",");
	Vec2i WindowPosition(std::stoi(Position[0]), std::stoi(Position[1]));

	const std::vector<std::string>& Size = Split(WindowConfig.GetValue("Size"), ",");
	Vec2i WindowSize(std::stoi(Size[0]), std::stoi(Size[1]));

	WindowConstructorParam Param;

	Param.Title = Convert(WindowConfig.GetValue("Title"));
	Param.PositionX = WindowPosition.x;
	Param.PositionY = WindowPosition.y;
	Param.Width = WindowSize.x;
	Param.Height = WindowSize.y;
	Param.bIsFullScreen = std::stoi(WindowConfig.GetValue("FullScreen")) ? true : false;

	Window_ = std::make_unique<Window>(Param);
}

void GameEngine::LoadFontFromConfig()
{
	Config& FontConfig = ContentManager::Get().LoadConfig("Font", "Font.config");

	const std::unordered_map<std::string, std::string>& FontKeyValues = FontConfig.GetConfigObject();

	for (const auto& FontKeyValue : FontKeyValues)
	{
		const std::vector<std::string>& FontInfo = Split(FontKeyValue.second, ",");

		const std::string& FontName = FontInfo[0];
		int32_t FontStartCodePoint = std::stoi(FontInfo[1]);
		int32_t FontEndCodePoint = std::stoi(FontInfo[2]);
		float FontSize = std::stof(FontInfo[3]);

		ContentManager::Get().LoadFont(FontKeyValue.first, FontName, FontStartCodePoint, FontEndCodePoint, FontSize);
	}
}

void GameEngine::LoadTextureFromConfig()
{
	Config& TextureConfig = ContentManager::Get().LoadConfig("Texture", "Texture.config");

	const std::unordered_map<std::string, std::string>& TextureKeyValyes = TextureConfig.GetConfigObject();

	for (auto& TextureKeyValye : TextureKeyValyes)
	{
		ContentManager::Get().LoadTexture2D(
			TextureKeyValye.first,
			TextureKeyValye.second
		);
	}
}

void GameEngine::LoadAudioFromConfig()
{
	Config& AudioConfig = ContentManager::Get().LoadConfig("Audio", "Audio.config");

	const std::unordered_map<std::string, std::string> AudioKeyValyes = AudioConfig.GetConfigObject();

	for (auto& AudioKeyValye : AudioKeyValyes)
	{
		ContentManager::Get().LoadSound(
			AudioKeyValye.first,
			AudioKeyValye.second
		);
	}
}
