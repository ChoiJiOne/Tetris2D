#include "Logger.h"
#include "Macro.h"
#include "GlobalProperty.h"

bool GlobalProperty::bIsInitialize = false;
std::string GlobalProperty::ExecuteDirectory;
std::string GlobalProperty::ProjectRootDirectory;
std::string GlobalProperty::SourceCodeDirectory;
std::string GlobalProperty::ResourceDirectory;
SDL_version GlobalProperty::Compiled;
SDL_version GlobalProperty::Linked;

void GlobalProperty::Initialize()
{
	if (!bIsInitialize)
	{
		SetupDirectory();
		SetupSDL2System();

#if defined(DEBUG) || defined(_DEBUG)
		Logger::Success("Success Initialize Global Property");
		Logger::Message(StringUtil::StringFormat("Project Root Directory : %s", ProjectRootDirectory.c_str()));
		Logger::Message(StringUtil::StringFormat("Source Code Directoryy : %s", SourceCodeDirectory.c_str()));
		Logger::Message(StringUtil::StringFormat("Resource Directory : %s", ResourceDirectory.c_str()));
		Logger::Message(StringUtil::StringFormat("Compile SDL version %u.%u.%u ...", Compiled.major, Compiled.minor, Compiled.patch));
		Logger::Message(StringUtil::StringFormat("Linking SDL version %u.%u.%u ...", Linked.major, Linked.minor, Linked.patch));
#endif

		bIsInitialize = true;
	}
}

void GlobalProperty::Release()
{
	if (bIsInitialize)
	{
		SDLNet_Quit();
		Mix_CloseAudio();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();

#if defined(DEBUG) || defined(_DEBUG)
		Logger::Success("Success Release Global Property");
#endif

		bIsInitialize = false;
	}
}

void GlobalProperty::SetupDirectory() noexcept
{
	ExecuteDirectory     = SDL_GetBasePath();
	ProjectRootDirectory = ExecuteDirectory + "../../../../";
	SourceCodeDirectory  = ExecuteDirectory + "../../../../Source/";
	ResourceDirectory    = ExecuteDirectory + "../../../../Resource/";
}

void GlobalProperty::SetupSDL2System()
{
	int32_t ImgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	CHECK_SDL_FAILED((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0));
	CHECK_SDL_FAILED((IMG_Init(ImgFlags) & ImgFlags));
	CHECK_SDL_FAILED((TTF_Init() != -1));
	CHECK_SDL_FAILED((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != -1));
	CHECK_SDL_FAILED((SDLNet_Init() != -1));

	SDL_VERSION(&Compiled);
	SDL_GetVersion(&Linked);
}
