// @third party code - BEGIN SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
// @third party code - END

#include "Macro.h"
#include "Engine.h"

Game::Engine::~Engine()
{
	SDL_Quit();
}

void Game::Engine::Initialize()
{
	CHECK((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0), SDL_GetError());
}
