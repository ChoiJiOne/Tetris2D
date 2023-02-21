#include "CommandLineManager.h"
#include "Text.hpp"
#include "Utils.hpp"

#include <Windows.h>

CommandLineManager::CommandLineManager()
{
	CommandLineA_ = GetCommandLineA();
	CommandLineW_ = GetCommandLineW();

	ParseCommandLineA();
	ParseCommandLineW();
}

void CommandLineManager::ParseCommandLineA()
{
	ArgumentsA_ = Split(CommandLineA_, " ");

	for (const auto& Argument : ArgumentsA_)
	{
		if (Argument.find("=") != std::string::npos)
		{
			std::vector<std::string> Tokens = Split(Argument, "=");
			OptionsA_.insert({ Tokens.front(), Tokens.back() });
		}
	}
}

void CommandLineManager::ParseCommandLineW()
{
	ArgumentsW_ = Split(CommandLineW_, L" ");

	for (const auto& Argument : ArgumentsW_)
	{
		if (Argument.find(L"=") != std::wstring::npos)
		{
			std::vector<std::wstring> Tokens = Split(Argument, L"=");
			OptionsW_.insert({ Tokens.front(), Tokens.back() });
		}
	}
}

bool CommandLineManager::HaveOption(const std::string& Option)
{
	return IsExistKey<std::string, std::string>(Option, OptionsA_);
}

bool CommandLineManager::HaveOption(const std::wstring& Option)
{
	return IsExistKey<std::wstring, std::wstring>(Option, OptionsW_);
}

std::string CommandLineManager::GetValue(const std::string& Option)
{
	CHECK(HaveOption(Option), "can't find command line option");
	return OptionsA_.at(Option);
}

std::wstring CommandLineManager::GetValue(const std::wstring& Option)
{
	CHECK(HaveOption(Option), "can't find command line option");
	return OptionsW_.at(Option);
}