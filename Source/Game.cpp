#include "Macro.h"
#include "Game.h"

Game::~Game()
{
}

void Game::Setup()
{
	CHECK_SDL_FAILED((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0));
}
/*
void Game::CreateWindow(SDL_Window* InWindow, const std::string InTitle, int32_t InX, int32_t InY, int32_t InWidth, int32_t InHeight, uint32_t InFlags)
{
	if (!InWindow)
	{

	}
}

void Game::DestroyWindow()
{
}

void Game::DestroyWindow(SDL_Window* InWindow)
{
}

void Game::CreateRenderer()
{
}

void Game::DestroyRenderer()
{
}
*/