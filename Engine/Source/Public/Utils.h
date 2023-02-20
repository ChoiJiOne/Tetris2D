#pragma once

#include <array>
#include <vector>
#include <unordered_map>


/**
 * @brief 파일을 읽고 버퍼에 저장합니다.
 *
 * @note 파일 경로의 문자열은 UTF-8 입니다.
 *
 * @see https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
 *
 * @param Path 파일의 경로입니다.
 * @param Buffer[out] 읽은 파일을 저장할 버퍼입니다.
 *
 * @throws
 * 파일 생성에 실패하면 C++ 표준 예외를 던집니다.
 * 파일 읽기에 실패하면 C++ 표준 예외를 던집니다.
 */
void ReadBufferFromFile(const std::string& Path, std::vector<uint8_t>& Buffer);


/**
 * @brief 파일을 읽고 버퍼에 저장합니다.
 *
 * @note 파일 경로의 문자열은 UTF-16 입니다.
 *
 * @param Path 파일의 경로입니다.
 * @param Buffer[out] 읽은 파일을 저장할 버퍼입니다.
 *
 * @throws
 * 파일 읽기에 실패하면 C++ 표준 예외를 던집니다.
 */
void ReadBufferFromFile(const std::wstring& Path, std::vector<uint8_t>& Buffer);