#include "Config.h"
#include "Text.hpp"
#include "Utils.hpp"

#include  <vector>

#include <windows.h>

Config::Config(const std::string& ResourcePath)
{
	std::vector<uint8_t> FileBuffer;
	ReadBufferFromFile(ResourcePath, FileBuffer);
	Config_ = ParseConfigFromBuffer(FileBuffer);
}

Config::~Config()
{
}

const std::string& Config::GetValue(const std::string& Key)
{
	bool bIsExist = IsExistKey<std::string, std::string>(Key, Config_);
	CHECK(bIsExist, "failed to get value in config");

	return Config_.at(Key);
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
