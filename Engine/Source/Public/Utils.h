#pragma once

#include <array>
#include <vector>
#include <unordered_map>


/**
 * @brief ������ �а� ���ۿ� �����մϴ�.
 *
 * @note ���� ����� ���ڿ��� UTF-8 �Դϴ�.
 *
 * @see https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
 *
 * @param Path ������ ����Դϴ�.
 * @param Buffer[out] ���� ������ ������ �����Դϴ�.
 *
 * @throws
 * ���� ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
 * ���� �б⿡ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
 */
void ReadBufferFromFile(const std::string& Path, std::vector<uint8_t>& Buffer);


/**
 * @brief ������ �а� ���ۿ� �����մϴ�.
 *
 * @note ���� ����� ���ڿ��� UTF-16 �Դϴ�.
 *
 * @param Path ������ ����Դϴ�.
 * @param Buffer[out] ���� ������ ������ �����Դϴ�.
 *
 * @throws
 * ���� �б⿡ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
 */
void ReadBufferFromFile(const std::wstring& Path, std::vector<uint8_t>& Buffer);