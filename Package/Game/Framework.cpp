#include "ResourceHelper.h"
#include "SDLHelper.h"

#include "Framework.h"

Game::Framework::~Framework()
{
	ResourceHelper::Cleanup();
	SDLHelper::Release();
}

void Game::Framework::Setup()
{
	SDLHelper::Init();
}