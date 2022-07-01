#include "GameSDLHelper.h"
#include "GameFramework.h"

Game::Framework::~Framework()
{
	SDLHelper::Release();
}

void Game::Framework::Setup()
{
	SDLHelper::Init();
}