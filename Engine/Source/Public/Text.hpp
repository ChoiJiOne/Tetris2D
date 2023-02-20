#pragma once

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
inline std::string Format(const std::string& Text, Args ... Argument)
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
inline std::wstring Format(const std::wstring& Text, Args ... Argument)
{
	size_t Size = static_cast<size_t>(std::swprintf(nullptr, 0, Text.c_str(), Argument ...)) + 1;

	auto Buffer = std::make_unique<wchar_t[]>(Size);
	std::swprintf(Buffer.get(), Size, Text.c_str(), Argument ...);

	return std::wstring(Buffer.get(), Buffer.get() + Size - 1);
}