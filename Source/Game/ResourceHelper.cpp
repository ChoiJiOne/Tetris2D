#include "Texture2D.h"
#include "TTFont.h"
#include "Macro.h"
#include "ResourceHelper.h"

// 리소스 헬퍼가 관리하는 텍스처 캐쉬입니다.
std::unordered_map<std::size_t, std::shared_ptr<Game::Texture2D>> Game::ResourceHelper::TextureCache;

// 리스소 헬퍼가 관리하는 폰트 캐쉬입니다.
std::unordered_map<std::size_t, std::shared_ptr<Game::TTFont>> Game::ResourceHelper::TTFontCache;

void Game::ResourceHelper::Cleanup()
{
	for (auto& Texture : TextureCache)
	{
		Texture.second.reset();
	}

	for (auto& Font : TTFontCache)
	{
		Font.second.reset();
	}
}

const Game::Texture2D& Game::ResourceHelper::CreateTexture2D(SDL_Renderer* InRenderer, const std::size_t& InHashKey, const std::string& InPath)
{
	auto TextureCacheIter = TextureCache.find(InHashKey);
	CHECK((TextureCacheIter == TextureCache.end()), "hash collision!");

	TextureCache.insert({ InHashKey, std::make_shared<Game::Texture2D>(InRenderer, InPath) });
	return *TextureCache.at(InHashKey).get();
}

const Game::TTFont& Game::ResourceHelper::CreateTTFont(SDL_Renderer* InRenderer, const std::size_t& InHashKey, const std::string& InPath, float InFontSize)
{
	auto FontCacheIter = TTFontCache.find(InHashKey);
	CHECK((FontCacheIter == TTFontCache.end()), "hash collision!");

	std::shared_ptr<Game::TTFont> Font = std::make_shared<Game::TTFont>();
	Font->Initialize(InRenderer, InPath, InFontSize);

	TTFontCache.insert({ InHashKey, Font });
	return *TTFontCache.at(InHashKey).get();
}

const Game::Texture2D& Game::ResourceHelper::GetTexture2D(const std::size_t& InHashKey)
{
	auto TextureCacheIter = TextureCache.find(InHashKey);
	CHECK((TextureCacheIter != TextureCache.end()), "don't exist hash key");

	return *TextureCache.at(InHashKey).get();
}

const Game::TTFont& Game::ResourceHelper::GetTTFont(const std::size_t& InHashKey)
{
	auto FontCacheIter = TTFontCache.find(InHashKey);
	CHECK((FontCacheIter != TTFontCache.end()), "don't exist hash key");

	return *TTFontCache.at(InHashKey).get();
}
