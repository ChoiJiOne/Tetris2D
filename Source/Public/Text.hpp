#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>


/**
 * @brief 형식화된 문자열을 반환합니다. 이 메서드는 snprintf를 대체하기 위한 메서드입니다.
 * 
 * @see https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
 *
 * @param Text 형식 문자열입니다.
 * @param ... Argument 포멧팅을 수행할 데이터를 지정하는 인수입니다.
 *
 * @return 포멧팅이 완료된 문자열을 반환합니다.
 */
template<typename ... Args>
static inline std::string Format(const std::string& Text, Args ... Argument)
{
	size_t Size = static_cast<size_t>(std::snprintf(nullptr, 0, Text.c_str(), Argument ...)) + 1;

	auto Buffer = std::make_unique<char[]>(Size);
	std::snprintf(Buffer.get(), Size, Text.c_str(), Argument ...);

	return std::string(Buffer.get(), Buffer.get() + Size - 1);
}


/**
 * @brief 형식화된 문자열을 반환합니다. 이 메서드는 swprintf를 대체하기 위한 메서드입니다.
 * 
 * @see https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
 *
 * @param Text 형식 문자열입니다.
 * @param ... Argument 포멧팅을 수행할 데이터를 지정하는 인수입니다.
 * 
 * @return 포멧팅이 완료된 문자열을 반환합니다.
 */
template<typename ... Args>
static inline std::wstring Format(const std::wstring& Text, Args ... Argument)
{
	size_t Size = static_cast<size_t>(std::swprintf(nullptr, 0, Text.c_str(), Argument ...)) + 1;

	auto Buffer = std::make_unique<wchar_t[]>(Size);
	std::swprintf(Buffer.get(), Size, Text.c_str(), Argument ...);

	return std::wstring(Buffer.get(), Buffer.get() + Size - 1);
}


/**
 * @brief 문자열을 특정 기준으로 나누어서 벡터로 만듭니다.
 *
 * @param Text 특정 기준으로 나누어서 벡터로 만들 문자열입니다.
 * @param Delimiter 문자열을 나눌 기준입니다.
 *
 * @return 나누어진 문자열의 벡터를 반환합니다.
 */
static inline std::vector<std::string> Split(std::string Text, const std::string& Delimiter)
{
	std::vector<std::string> Tokens;
	std::size_t Position = 0;

	while ((Position = Text.find(Delimiter)) != std::string::npos)
	{
		Tokens.push_back(Text.substr(0, Position));
		Text.erase(0, Position + Delimiter.length());
	}

	Tokens.push_back(Text);
	return Tokens;
}


/**
 * @brief 문자열을 특정 기준으로 나누어서 벡터로 만듭니다.
 *
 * @param Text 특정 기준으로 나누어서 벡터로 만들 문자열입니다.
 * @param Delimiter 문자열을 나눌 기준입니다.
 *
 * @return 나누어진 문자열의 벡터를 반환합니다.
 */
static inline std::vector<std::wstring> Split(std::wstring Text, const std::wstring& Delimiter)
{
	std::vector<std::wstring> Tokens;
	std::size_t Position = 0;

	while ((Position = Text.find(Delimiter)) != std::wstring::npos)
	{
		Tokens.push_back(Text.substr(0, Position));
		Text.erase(0, Position + Delimiter.length());
	}

	Tokens.push_back(Text);
	return Tokens;
}