#include "Texture2D.h"
#include "TTFont.h"
#include "Macro.h"
#include "ResourceManager.h"

std::unordered_map<std::size_t, std::shared_ptr<Game::Texture2D>> Game::ResourceManager::TextureCache;
std::unordered_map<std::size_t, std::shared_ptr<Game::TTFont>> Game::ResourceManager::TTFontCache;

void Game::ResourceManager::Cleanup()
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

const Game::Texture2D& Game::ResourceManager::CreateTexture2D(SDL_Renderer* InRenderer, const std::size_t& InHashKey, const std::string& InPath)
{
	auto TextureCacheIter = TextureCache.find(InHashKey);
	CHECK((TextureCacheIter == TextureCache.end()), "hash collision!");

	TextureCache.insert({ InHashKey, std::make_shared<Game::Texture2D>(InRenderer, InPath) });
	return *TextureCache.at(InHashKey).get();
}

const Game::TTFont& Game::ResourceManager::CreateTTFont(SDL_Renderer* InRenderer, const std::size_t& InHashKey, const std::string& InPath, float InFontSize)
{
	auto FontCacheIter = TTFontCache.find(InHashKey);
	CHECK((FontCacheIter == TTFontCache.end()), "hash collision!");

	std::shared_ptr<Game::TTFont> Font = std::make_shared<Game::TTFont>();
	Font->Initialize(InRenderer, InPath, InFontSize);

	TTFontCache.insert({ InHashKey, Font });
	return *TTFontCache.at(InHashKey).get();
}

const Game::Texture2D& Game::ResourceManager::GetTexture2D(const std::size_t& InHashKey)
{
	auto TextureCacheIter = TextureCache.find(InHashKey);
	CHECK((TextureCacheIter != TextureCache.end()), "don't exist hash key");

	return *TextureCache.at(InHashKey).get();
}

const Game::TTFont& Game::ResourceManager::GetTTFont(const std::size_t& InHashKey)
{
	auto FontCacheIter = TTFontCache.find(InHashKey);
	CHECK((FontCacheIter != TTFontCache.end()), "don't exist hash key");

	return *TTFontCache.at(InHashKey).get();
}
