#pragma once

#include "Macro.h"
#include "Vector.hpp"
#include "Matrix.hpp"


/**
 * @brief float 타입의 파이(π) 값입니다.
 */
const float PI_F = 3.1415926535F;


/**
 * @brief double 타입의 파이(π) 값입니다.
 */
const double PI_D = 3.1415926535897931;


/**
 * @brief float 타입의 타입의 엡실론(ε) 값입니다.
 */
const float EPSILON_F = std::numeric_limits<float>::epsilon();


/**
 * @brief double 타입의 엡실론(ε) 값입니다.
 */
const double EPSILON_D = std::numeric_limits<double>::epsilon();


/**
 * @brief float 타입의 무한대 값입니다.
 */
const float INFINITY_F = std::numeric_limits<float>::infinity();


/**
 * @brief double 타입의 무한대 값입니다.
 */
const double INFINITY_D = std::numeric_limits<double>::infinity();


/**
 * @brief float 타입의 음의 무한대 값입니다.
 */
const float NINFINITY_F = -std::numeric_limits<float>::infinity();


/**
 * @brief double 타입의 음의 무한대 값입니다.
 */
const double NINFINITY_D = -std::numeric_limits<double>::infinity();


/**
 * @brief 라디안 각을 육십분법 각으로 변환합니다.
 *
 * @param Radian 변환할 라디안 각입니다.
 *
 * @return 변환된 육십분법 각입니다.
 */
inline float ToDegree(float Radian)
{
	return (Radian * 180.0f) / PI_F;
}


/**
 * @brief 라디안 각을 육십분법 각으로 변환합니다.
 *
 * @param Radian 변환할 라디안 각입니다.
 *
 * @return 변환된 육십분법 각입니다.
 */
inline double ToDegree(double Radian)
{
	return (Radian * 180.0) / PI_D;
}


/**
 * @brief 육십분법 각을 라디안 각으로 변환합니다.
 *
 * @param Degree 변환할 육십분법 각입니다.
 *
 * @return 변환된 라디안 각입니다.
 */
inline float ToRadian(float Degree)
{
	return (Degree * PI_F) / 180.0f;
}


/**
 * @brief 육십분법 각을 라디안 각으로 변환합니다.
 *
 * @param Degree 변환할 육십분법 각입니다.
 *
 * @return 변환된 라디안 각입니다.
 */
inline double ToRadian(double Degree)
{
	return (Degree * PI_D) / 180.0;
}


/**
 * @brief 0에 한없이 가까운 값인지 확인합니다.
 *
 * @param Value 0에 한없이 가까운지 확인할 값입니다.
 * @param Epsilon 엡실론 값입니다.
 * 
 * @return 엡실론 값보다 작다면 true, 그렇지 않다면 false를 반환합니다.
 */
inline bool IsNearZero(const float& Value, const float Epsilon = EPSILON_F)
{
	return (fabs(Value) <= Epsilon);
}


/**
 * @brief 직교 투영 행렬을 얻습니다.
 * 
 * @note 왼손 좌표계 기준입니다.
 * 
 * @see https://learn.microsoft.com/ko-kr/windows/win32/api/directxmath/nf-directxmath-xmmatrixorthographiclh
 * 
 * @param ViewWidth 가까운 클리핑 평면에 있는 frustum의 너비입니다.
 * @param ViewHeight 가까운 클리핑 평면에 있는 frustum의 높이입니다.
 * @param NearZ 가까운 클리핑 평면까지의 거리입니다.
 * @param FarZ 원거리 클리핑 평면까지의 거리입니다.
 * 
 * @return 왼손 좌표계 기준의 직교 투영 행렬을 반환합니다.
 */
inline Matrix4x4F GetOrthographicMatrix(float ViewWidth, float ViewHeight, float NearZ, float FarZ)
{
	CHECK(!IsNearZero(ViewWidth), "view width is zero");
	CHECK(!IsNearZero(ViewHeight), "view height is zero");
	CHECK(!IsNearZero(FarZ - NearZ), "view height is zero");
	
	float Range = 1.0f / (FarZ - NearZ);

	return Matrix4x4F(
		2.0f / ViewWidth,              0.0f,           0.0f, 0.0f,
		            0.0f, 2.0f / ViewHeight,           0.0f, 0.0f,
		            0.0f,              0.0f,         +Range, 0.0f,
		            0.0f,              0.0f, -Range * NearZ, 1.0f
	);
}


/**
 * @brief 2D 평면 상의 원점 중심 회전 행렬을 얻습니다.
 * 
 * @param Angle 라디안 각도 기준의 회전 각입니다.
 * 
 * @return 회전 행렬을 얻습니다.
 */
inline Matrix4x4F GetRotateMatrix(float Angle)
{
	float Sin = std::sin(Angle);
	float Cos = std::cos(Angle);

	return Matrix4x4F(
		+Cos,   -Sin, 0.0f, 0.0f,
		+Sin,   +Cos, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, 1.0f
	);
}