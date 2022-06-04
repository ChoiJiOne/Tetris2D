#include "Logger.h"
#include "Macro.h"
#include "GlobalProperty.h"

bool GlobalProperty::bIsInitialize = false;
std::string GlobalProperty::ExecuteDirectory;
std::string GlobalProperty::ProjectRootDirectory;
std::string GlobalProperty::SourceCodeDirectory;
std::string GlobalProperty::ResourceDirectory;

void GlobalProperty::Initialize()
{
	if (!bIsInitialize)
	{
		ExecuteDirectory = SDL_GetBasePath();
		ProjectRootDirectory = ExecuteDirectory + "../../../../";
		SourceCodeDirectory = ExecuteDirectory + "../../../../Source/";
		ResourceDirectory = ExecuteDirectory + "../../../../Resource/";

		CHECK_SDL_FAILED((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0));

#if defined(DEBUG) || defined(_DEBUG)
		Logger::Success("Success Initialize GlobalProperty");
		Logger::Success(StringUtil::StringFormat("Project Root Directory : %s", ProjectRootDirectory.c_str()));
		Logger::Success(StringUtil::StringFormat("Source Code Directoryy : %s", SourceCodeDirectory.c_str()));
		Logger::Success(StringUtil::StringFormat("Resource Directory : %s", ResourceDirectory.c_str()));
#endif

		bIsInitialize = true;
	}
}

void GlobalProperty::Release()
{
	if (bIsInitialize)
	{
		SDL_Quit();

#if defined(DEBUG) || defined(_DEBUG)
		Logger::Success("Success Release GlobalProperty");
#endif

		bIsInitialize = false;
	}
}
