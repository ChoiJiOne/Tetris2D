#include "ContentManager.h"
#include "CommandLineManager.h"
#include "Font.h"
#include "GraphicsManager.h"
#include "Sound.h"
#include "Shader.h"
#include "Texture2D.h"

// @third party code - BEGIN
#include <miniaudio/miniaudio.h>
// @third party code - END

ContentManager::ContentManager()
{
	AudioEngine_ = std::make_unique<ma_engine>();
	ma_result Result = ma_engine_init(nullptr, AudioEngine_.get());
	CHECK((Result == MA_SUCCESS), "failed to initialize audio engine");

	DeviceForTexture_ = GraphicsManager::Get().GetDevice();
	CHECK((DeviceForTexture_ != nullptr), "failed to initialize GraphicsManager");

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
	bool bIsCollision = IsCollision<std::string, std::unique_ptr<Texture2D>>(Signature, Textures_);
	CHECK(!bIsCollision, "collision texture signature");

	const std::string& Path = ContentPath_ + "Texture\\" + FileName;
	Textures_[Signature] = std::make_unique<Texture2D>(DeviceForTexture_, Path);

	return *Textures_[Signature].get();
}

Texture2D& ContentManager::GetTexture2D(const std::string& Signature)
{
	bool bIsCollision = IsCollision<std::string, std::unique_ptr<Texture2D>>(Signature, Textures_);
	CHECK(bIsCollision, "doesn't exist texture signature");
	
	return *Textures_[Signature].get();
}

void ContentManager::RemoveTexture2D(const std::string& Signature)
{
	Remove<std::string, std::unique_ptr<Texture2D>>(Signature, Textures_);
}

Font& ContentManager::LoadFont(const std::string& Signature, const std::string& FileName, int32_t BeginCodePoint, int32_t EndCodePoint, float FontSize)
{
	bool bIsCollision = IsCollision<std::string, std::unique_ptr<Font>>(Signature, Fonts_);
	CHECK(!bIsCollision, "collision font signature");

	const std::string& Path = ContentPath_ + "Font\\" + FileName;
	Fonts_[Signature] = std::make_unique<Font>(DeviceForTexture_, Path, BeginCodePoint, EndCodePoint, FontSize);

	return *Fonts_[Signature].get();
}

Font& ContentManager::GetFont(const std::string& Signature)
{
	bool bIsCollision = IsCollision<std::string, std::unique_ptr<Font>>(Signature, Fonts_);
	CHECK(bIsCollision, "doesn't exist font signature");

	return *Fonts_[Signature].get();
}

void ContentManager::RemoveFont(const std::string& Signature)
{
	Remove<std::string, std::unique_ptr<Font>>(Signature, Fonts_);
}

Sound& ContentManager::LoadSound(const std::string& Signature, const std::string& FileName)
{
	bool bIsCollision = IsCollision<std::string, std::unique_ptr<Sound>>(Signature, Sounds_);
	CHECK(!bIsCollision, "collision sound signature");

	const std::string& Path = ContentPath_ + "Sound\\" + FileName;
	Sounds_[Signature] = std::make_unique<Sound>(AudioEngine_.get(), Path);

	return *Sounds_[Signature].get();
}

Sound& ContentManager::GetSound(const std::string& Signature)
{
	bool bIsCollision = IsCollision<std::string, std::unique_ptr<Sound>>(Signature, Sounds_);
	CHECK(bIsCollision, "doesn't exist sound signature");

	return *Sounds_[Signature].get();
}

void ContentManager::RemoveSound(const std::string& Signature)
{
	Remove<std::string, std::unique_ptr<Sound>>(Signature, Sounds_);
}
