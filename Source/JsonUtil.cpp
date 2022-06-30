#include "../Public/Macro.h"
#include "../Public/JsonUtil.h"

nlohmann::json JsonUtil::LoadJsonFile(const std::string& InPath)
{
	std::ifstream Ifs(InPath);
	CHECK_FAILED((Ifs.is_open()), "failed to load json file");

	nlohmann::json OutputJson;
	Ifs >> OutputJson;

	Ifs.close();
	return OutputJson;
}

nlohmann::json JsonUtil::LoadJsonFile(const std::wstring& InPath)
{
	std::ifstream Ifs(InPath);
	CHECK_FAILED((Ifs.is_open()), "failed to load json file");

	nlohmann::json OutputJson;
	Ifs >> OutputJson;

	Ifs.close();
	return OutputJson;
}