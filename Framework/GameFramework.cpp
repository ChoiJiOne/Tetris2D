#include "Macro.h"
#include "GameFramework.h"

GameFramework::~GameFramework()
{
	if (bIsInitialize)
	{
		SDL_Quit();

		bIsInitialize = false;
	}
}

void GameFramework::Setup()
{
	if (!bIsInitialize)
	{
		ExecuteDirectory     = SDL_GetBasePath();
		ProjectRootDirectory = ExecuteDirectory + "../../../../";
		FrameworkDirectory   = ExecuteDirectory + "../../../../Framework/";
		ResourceDirectory    = ExecuteDirectory + "../../../../Resource/";

		CHECK_SDL_FAILED((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0));

		SDL_VERSION(&CompiledVersion);
		SDL_GetVersion(&LinkedVersion);

		bIsInitialize = true;
	}
}
