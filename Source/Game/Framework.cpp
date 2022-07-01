#include "SDLHelper.h"
#include "Framework.h"

Game::Framework::~Framework()
{
	SDLHelper::Release();
}

void Game::Framework::Setup()
{
	SDLHelper::Init();
}