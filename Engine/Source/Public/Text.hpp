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