#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include <windows.h>


/**
 * @brief ����ȭ�� ���ڿ��� ��ȯ�մϴ�. �� �޼���� snprintf�� ��ü�ϱ� ���� �޼����Դϴ�.
 * 
 * @see https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
 *
 * @param Text ���� ���ڿ��Դϴ�.
 * @param ... Argument �������� ������ �����͸� �����ϴ� �μ��Դϴ�.
 *
 * @return �������� �Ϸ�� ���ڿ��� ��ȯ�մϴ�.
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
 * @brief ����ȭ�� ���ڿ��� ��ȯ�մϴ�. �� �޼���� swprintf�� ��ü�ϱ� ���� �޼����Դϴ�.
 * 
 * @see https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
 *
 * @param Text ���� ���ڿ��Դϴ�.
 * @param ... Argument �������� ������ �����͸� �����ϴ� �μ��Դϴ�.
 * 
 * @return �������� �Ϸ�� ���ڿ��� ��ȯ�մϴ�.
 */
template<typename ... Args>
inline std::wstring Format(const std::wstring& Text, Args ... Argument)
{
	size_t Size = static_cast<size_t>(std::swprintf(nullptr, 0, Text.c_str(), Argument ...)) + 1;

	auto Buffer = std::make_unique<wchar_t[]>(Size);
	std::swprintf(Buffer.get(), Size, Text.c_str(), Argument ...);

	return std::wstring(Buffer.get(), Buffer.get() + Size - 1);
}


/**
 * @brief ���ڿ��� Ư�� �������� ����� ���ͷ� ����ϴ�.
 *
 * @param Text Ư�� �������� ����� ���ͷ� ���� ���ڿ��Դϴ�.
 * @param Delimiter ���ڿ��� ���� �����Դϴ�.
 *
 * @return �������� ���ڿ��� ���͸� ��ȯ�մϴ�.
 */
inline std::vector<std::string> Split(std::string Text, const std::string& Delimiter)
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
 * @brief ���ڿ��� Ư�� �������� ����� ���ͷ� ����ϴ�.
 *
 * @param Text Ư�� �������� ����� ���ͷ� ���� ���ڿ��Դϴ�.
 * @param Delimiter ���ڿ��� ���� �����Դϴ�.
 *
 * @return �������� ���ڿ��� ���͸� ��ȯ�մϴ�.
 */
inline std::vector<std::wstring> Split(std::wstring Text, const std::wstring& Delimiter)
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


/**
 * @brief UTF-8 ���ڿ��� UTF-16 ���ڿ��� ��ȯ�մϴ�.
 * 
 * @param UTF8Text UTF-8 ����� ���ڿ��Դϴ�.
 * 
 * @return ��ȯ�� UTF-16 ���ڿ��� ��ȯ�մϴ�.
 */
inline std::wstring Convert(const std::string UTF8Text)
{
	int32_t Size = MultiByteToWideChar(CP_UTF8, 0, &UTF8Text[0], static_cast<int32_t>(UTF8Text.size()), nullptr, 0);
	std::wstring UTF16Text(Size, 0);
	MultiByteToWideChar(CP_UTF8, 0, &UTF8Text[0], static_cast<int32_t>(UTF8Text.size()), &UTF16Text[0], Size);
	return UTF16Text;
}


/**
 * @brief UTF-16 ���ڿ��� UTF-8 ���ڿ��� ��ȯ�մϴ�.
 * 
 * @param UTF16Text UTF-16 ����� ���ڿ��Դϴ�.
 * 
 * @return ��ȯ�� UTF-8 ���ڿ��� ��ȯ�մϴ�.
 */
inline std::string Convert(const std::wstring& UTF16Text)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, &UTF16Text[0], static_cast<int32_t>(UTF16Text.size()), nullptr, 0, nullptr, nullptr);
	std::string UTF8Text(Size, 0);
	WideCharToMultiByte(CP_UTF8, 0, &UTF16Text[0], static_cast<int32_t>(UTF16Text.size()), &UTF8Text[0], Size, nullptr, nullptr);
	return UTF8Text;
}