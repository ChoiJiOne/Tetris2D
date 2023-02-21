#include "ContentManager.h"
#include "CommandLineManager.h"
#include "Config.h"
#include "Font.h"
#include "GraphicsManager.h"
#include "Sound.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Utils.hpp"

// @third party code - BEGIN
#include <miniaudio/miniaudio.h>
// @third party code - END

ContentManager::ContentManager()
{
	AudioEngine_ = std::make_unique<ma_engine>();
	ma_result Result = ma_engine_init(nullptr, AudioEngine_.get());
	CHECK((Result == MA_SUCCESS), "failed to initialize audio engine");

	ContentPath_ = CommandLineManager::Get().GetValue("-Content");
	CHECK((!ContentPath_.empty()), "failed to set content path");
}

ContentManager::~ContentManager()
{
	for (auto& ManageTexture : Textures_)
	{
		ManageTexture.second.reset();
	}

	for (auto& ManageFont : Fonts_)
	{
		ManageFont.second.reset();
	}

	for (auto& ManageSound : Sounds_)
	{
		ManageSound.second.reset();
	}

	ma_engine_uninit(AudioEngine_.get());
	AudioEngine_.reset();
}

Texture2D& ContentManager::LoadTexture2D(const std::string& Signature, const std::string& FileName)
{
	bool bIsExist = IsExistKey<std::string, std::unique_ptr<Texture2D>>(Signature, Textures_);
	CHECK(!bIsExist, "collision texture signature");

	const std::string& Path = ContentPath_ + "Texture\\" + FileName;
	Textures_[Signature] = std::make_unique<Texture2D>(GraphicsManager::Get().GetDevice(), Path);

	return *Textures_[Signature].get();
}

Texture2D& ContentManager::GetTexture2D(const std::string& Signature)
{
	bool bIsExist = IsExistKey<std::string, std::unique_ptr<Texture2D>>(Signature, Textures_);
	CHECK(bIsExist, "doesn't exist texture signature");
	
	return *Textures_[Signature].get();
}

void ContentManager::RemoveTexture2D(const std::string& Signature)
{
	RemoveValue<std::string, std::unique_ptr<Texture2D>>(Signature, Textures_);
}

Font& ContentManager::LoadFont(const std::string& Signature, const std::string& FileName, int32_t BeginCodePoint, int32_t EndCodePoint, float FontSize)
{
	bool bIsExist = IsExistKey<std::string, std::unique_ptr<Font>>(Signature, Fonts_);
	CHECK(!bIsExist, "collision font signature");

	const std::string& Path = ContentPath_ + "Font\\" + FileName;
	Fonts_[Signature] = std::make_unique<Font>(GraphicsManager::Get().GetDevice(), Path, BeginCodePoint, EndCodePoint, FontSize);

	return *Fonts_[Signature].get();
}

Font& ContentManager::GetFont(const std::string& Signature)
{
	bool bIsExist = IsExistKey<std::string, std::unique_ptr<Font>>(Signature, Fonts_);
	CHECK(bIsExist, "doesn't exist font signature");

	return *Fonts_[Signature].get();
}

void ContentManager::RemoveFont(const std::string& Signature)
{
	RemoveValue<std::string, std::unique_ptr<Font>>(Signature, Fonts_);
}

Sound& ContentManager::LoadSound(const std::string& Signature, const std::string& FileName)
{
	bool bIsExist = IsExistKey<std::string, std::unique_ptr<Sound>>(Signature, Sounds_);
	CHECK(!bIsExist, "collision sound signature");

	const std::string& Path = ContentPath_ + "Audio\\" + FileName;
	Sounds_[Signature] = std::make_unique<Sound>(AudioEngine_.get(), Path);

	return *Sounds_[Signature].get();
}

Sound& ContentManager::GetSound(const std::string& Signature)
{
	bool bIsExist = IsExistKey<std::string, std::unique_ptr<Sound>>(Signature, Sounds_);
	CHECK(bIsExist, "doesn't exist sound signature");

	return *Sounds_[Signature].get();
}

void ContentManager::RemoveSound(const std::string& Signature)
{
	RemoveValue<std::string, std::unique_ptr<Sound>>(Signature, Sounds_);
}

Config& ContentManager::LoadConfig(const std::string& Signature, const std::string& FileName)
{
	bool bIsExist = IsExistKey<std::string, std::unique_ptr<Config>>(Signature, Configs_);
	CHECK(!bIsExist, "collision config signature");

	const std::string& Path = ContentPath_ + "Config\\" + FileName;
	Configs_[Signature] = std::make_unique<Config>(Path);

	return *Configs_[Signature].get();
}

Config& ContentManager::GetConfig(const std::string& Signature)
{
	bool bIsExist = IsExistKey<std::string, std::unique_ptr<Config>>(Signature, Configs_);
	CHECK(bIsExist, "doesn't exist config signature");

	return *Configs_[Signature].get();
}

void ContentManager::RemoveConfig(const std::string& Signature)
{
	RemoveValue<std::string, std::unique_ptr<Config>>(Signature, Configs_);
}
