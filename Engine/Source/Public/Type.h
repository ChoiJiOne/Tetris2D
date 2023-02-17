#pragma once

#include <string>


/**
 * @brief 크기가 명시된 정수 자료형을 선언합니다.
 *
 * @see
 * int8 https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/HAL/int8/
 * int16 https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/HAL/int16/
 * int32 https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/HAL/int32/
 * int64 https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/HAL/int64/
 * uint8 https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/HAL/uint8/
 * uint16 https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/HAL/uint16/
 * uint32 https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/HAL/uint32/
 * uint64 https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/HAL/uint64/
 */
using int8   = signed char;
using int16  = short;
using int32  = int;
using int64  = long long;
using uint8  = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;


/**
 * @brief 문자열 자료형을 선언합니다.
 */
using UTF8 = std::string;
using UTF16 = std::wstring;