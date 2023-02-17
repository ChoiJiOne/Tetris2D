#pragma once

#include "Type.h"

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include <windows.h>


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
inline UTF8 FormatText(const UTF8& Text, Args ... Argument)
{
	int32 Size = static_cast<int32>(std::snprintf(nullptr, 0, Text.c_str(), Argument ...)) + 1;

	auto Buffer = std::make_unique<int8[]>(Size);
	std::snprintf(Buffer.get(), Size, Text.c_str(), Argument ...);

	return UTF8(Buffer.get(), Buffer.get() + Size - 1);
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
inline UTF16 FormatText(const UTF16& Text, Args ... Argument)
{
	int32 Size = static_cast<int32>(std::swprintf(nullptr, 0, Text.c_str(), Argument ...)) + 1;

	auto Buffer = std::make_unique<wchar_t[]>(Size);
	std::swprintf(Buffer.get(), Size, Text.c_str(), Argument ...);

	return UTF16(Buffer.get(), Buffer.get() + Size - 1);
}


/**
 * @brief 문자열을 특정 기준으로 나누어서 벡터로 만듭니다.
 *
 * @param Text 특정 기준으로 나누어서 벡터로 만들 문자열입니다.
 * @param Delimiter 문자열을 나눌 기준입니다.
 *
 * @return 나누어진 문자열의 벡터를 반환합니다.
 */
inline std::vector<UTF8> SplitText(const UTF8& Text, const UTF8& Delimiter)
{
	UTF8 ParseText = Text;
	std::vector<UTF8> Tokens;
	uint64 Position = 0;

	while ((Position = ParseText.find(Delimiter)) != std::string::npos)
	{
		Tokens.push_back(ParseText.substr(0, Position));
		ParseText.erase(0, Position + Delimiter.length());
	}

	Tokens.push_back(ParseText);
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
inline std::vector<UTF16> SplitText(const UTF16& Text, const UTF16& Delimiter)
{
	UTF16 ParseText = Text;
	std::vector<UTF16> Tokens;
	uint64 Position = 0;

	while ((Position = ParseText.find(Delimiter)) != std::wstring::npos)
	{
		Tokens.push_back(ParseText.substr(0, Position));
		ParseText.erase(0, Position + Delimiter.length());
	}

	Tokens.push_back(ParseText);
	return Tokens;
}


/**
 * @brief UTF-8 문자열을 UTF-16 문자열로 변환합니다.
 *
 * @param UTF8Text UTF-8 기반의 문자열입니다.
 *
 * @return 변환된 UTF-16 문자열을 반환합니다.
 */
inline UTF16 ConvertText(const UTF8& Text)
{
	int32 Size = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&Text[0]), static_cast<int32>(Text.size()), nullptr, 0);

	UTF16 NewConvertText(Size, 0);

	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&Text[0]), static_cast<int32>(Text.size()), &NewConvertText[0], Size);

	return NewConvertText;
}


/**
 * @brief UTF-16 문자열을 UTF-8 문자열로 변환합니다.
 *
 * @param UTF16Text UTF-16 기반의 문자열입니다.
 *
 * @return 변환된 UTF-8 문자열을 반환합니다.
 */
inline UTF8 ConvertText(const UTF16& Text)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, reinterpret_cast<const wchar_t*>(&Text[0]), static_cast<int32_t>(Text.size()), nullptr, 0, nullptr, nullptr);

	UTF8 NewConvertText(Size, 0);

	WideCharToMultiByte(CP_UTF8, 0, &Text[0], static_cast<int32_t>(Text.size()), reinterpret_cast<char*>(&NewConvertText[0]), Size, nullptr, nullptr);
	
	return NewConvertText;
}