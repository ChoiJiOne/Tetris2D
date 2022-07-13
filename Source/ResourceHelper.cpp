#include "Texture2D.h"
#include "Font.h"
#include "Macro.h"

#include "ResourceHelper.h"

// 리소스 헬퍼가 관리하는 텍스처 캐쉬입니다.
std::unordered_map<std::size_t, std::shared_ptr<Game::Texture2D>> Game::ResourceHelper::TextureCache;

// 리스소 헬퍼가 관리하는 폰트 캐쉬입니다.
std::unordered_map<std::size_t, std::shared_ptr<Game::Font>> Game::ResourceHelper::FontCache;

void Game::ResourceHelper::Cleanup()
{
	for (auto& Texture : TextureCache)
	{
		Texture.second.reset();
	}

	for (auto& Font : FontCache)
	{
		Font.second.reset();
	}
}

const Game::Texture2D& Game::ResourceHelper::CreateTexture2D(SDL_Renderer* InRenderer, const std::size_t& InHashKey, const std::string& InPath)
{
	auto TextureCacheIter = TextureCache.find(InHashKey);
	CHECK_FAILED((TextureCacheIter == TextureCache.end()), "hash collision!");

	TextureCache.insert({ InHashKey, std::make_shared<Game::Texture2D>(InRenderer, InPath) });
	return *TextureCache.at(InHashKey).get();
}

const Game::Font& Game::ResourceHelper::CreateFont(SDL_Renderer* InRenderer, const std::size_t& InHashKey, const std::string& InPath, float InFontSize)
{
	auto FontCacheIter = FontCache.find(InHashKey);
	CHECK_FAILED((FontCacheIter == FontCache.end()), "hash collision!");

	FontCache.insert({ InHashKey, std::make_shared<Game::Font>(InRenderer, InPath, InFontSize) });
	return *FontCache.at(InHashKey).get();
}

const Game::Texture2D& Game::ResourceHelper::GetTexture2D(const std::size_t& InHashKey)
{
	auto TextureCacheIter = TextureCache.find(InHashKey);
	CHECK_FAILED((TextureCacheIter != TextureCache.end()), "don't exist hash key");

	return *TextureCache.at(InHashKey).get();
}

const Game::Font& Game::ResourceHelper::GetFont(const std::size_t& InHashKey)
{
	auto FontCacheIter = FontCache.find(InHashKey);
	CHECK_FAILED((FontCacheIter != FontCache.end()), "don't exist hash key");

	return *FontCache.at(InHashKey).get();
}
