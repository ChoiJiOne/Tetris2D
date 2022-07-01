#include "GameSDLUtility.h"
#include "GameFramework.h"

Game::Framework::~Framework()
{
	SDLUtility::Release();
}

void Game::Framework::Setup()
{
	SDLUtility::Init();
}