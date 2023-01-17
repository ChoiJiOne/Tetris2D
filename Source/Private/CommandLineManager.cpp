#include "CommandLineManager.h"
#include "Text.hpp"

#include <Windows.h>

CommandLineManager::CommandLineManager()
{
	CommandLine_ = GetCommandLineA();
	Arguments_ = Split(CommandLine_, " ");

	for (const auto& Argument : Arguments_)
	{
		if (Argument.find("=") != std::string::npos)
		{
			std::vector<std::string> Tokens = Split(Argument, "=");
			Options_.insert({ Tokens.front(), Tokens.back() });
		}
	}
}

bool CommandLineManager::HaveOption(const std::string& InOption)
{
	return Options_.find(InOption) != Options_.end();
}

std::string CommandLineManager::GetValue(const std::string& InOption)
{
	CHECK(HaveOption(InOption), "can't find command line option");
	return Options_.at(InOption);
}