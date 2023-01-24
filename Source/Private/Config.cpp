#include "Config.h"
#include "Text.hpp"

#include  <vector>

#include <windows.h>

Config::Config(const std::string& ResourcePath)
{
	std::vector<uint8_t> FileBuffer;
	CHECK(LoadConfigFromFile(ResourcePath, FileBuffer), "failed to load config");
	Config_ = ParseConfigFromBuffer(FileBuffer);
}

Config::~Config()
{
}

const std::string& Config::GetValue(const std::string& Key)
{
	return IsExistKey<std::string, std::string>(Key, Config_) ? Config_.at(Key) : "";
}

bool Config::LoadConfigFromFile(const std::string& ResourcePath, std::vector<uint8_t>& Buffer)
{
	HANDLE ConfigFileHandle = CreateFileA(ResourcePath.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	DWORD FileSize = GetFileSize(ConfigFileHandle, nullptr);

	Buffer.resize(FileSize);

	bool bIsSuccessed = true;
	bIsSuccessed = ReadFile(ConfigFileHandle, &Buffer[0], FileSize, nullptr, nullptr);
	bIsSuccessed = CloseHandle(ConfigFileHandle);

	return bIsSuccessed;
}

std::unordered_map<std::string, std::string> Config::ParseConfigFromBuffer(const std::vector<uint8_t>& Buffer)
{
	std::string BufferString(Buffer.begin(), Buffer.end());
	std::vector<std::string> ReadLines = Split(BufferString, "\r\n");

	std::unordered_map<std::string, std::string> Configure;
	for (auto& ReadLine : ReadLines)
	{
		std::vector<std::string> KeyValue = Split(ReadLine, "=");
		CHECK((KeyValue.size() == 2), "invalid config key and value");

		Configure.insert({ KeyValue[0], KeyValue[1] });
	}

	return Configure;
}
