#pragma once

#include <cstdint>


/**
 * @brief 임의의 정수를 생성합니다.
 *
 * @param MinValue 생성할 난수 범위의 최솟값입니다.
 * @param MaxValue 생성할 난수 범위의 최댓값입니다.
 *
 * @return 생성된 임의의 정수를 반환합니다.
 */
int32_t GenerateRandomInt(int32_t MinValue, int32_t MaxValue);


/**
 * @brief 임의의 실수를 생성합니다.
 *
 * @param MinValue 생성할 난수 범위의 최솟값입니다.
 * @param MaxValue 생성할 난수 범위의 최댓값입니다.
 *
 * @return 생성된 임의의 실수를 반환합니다.
 */
float GenerateRandomFloat(float MinValue, float MaxValue);