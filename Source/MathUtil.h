#pragma once

// 표준 라이브러리를 사용하기 위한 헤더 선언을 추가합니다.
#include "CommonHeader.h"


// int32_t 타입의 2차원 벡터입니다.
struct Vec2i
{
	// 생성자입니다.
	Vec2i() noexcept : x(0), y(0) {}


	// 생성자입니다.
	// 
	// @param InX - 2차원 벡터의 첫 번째 성분입니다.
	// @param InY - 2차원 벡터의 두 번째 성분입니다.
	Vec2i(int32_t InX, int32_t InY) noexcept : x(InX), y(InY) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 2차원 벡터입니다.
	Vec2i(const Vec2i& InV) noexcept : x(InV.x), y(InV.y) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 2차원 벡터입니다.
	Vec2i(Vec2i&& InV) noexcept : x(InV.x), y(InV.y) {}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 2차원 벡터입니다.
	Vec2i& operator=(const Vec2i& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;

		return *this;
	}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 2차원 벡터입니다.
	Vec2i& operator=(Vec2i&& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;

		return *this;
	}


	// int32_t 타입 2차원 벡터의 첫 번째 성분입니다.
	int32_t x = 0;


	// int32_t 타입 2차원 벡터의 두 번째 성분입니다.
	int32_t y = 0;
};


// float 타입의 2차원 벡터입니다.
struct Vec2f
{
	// 생성자입니다.
	Vec2f() noexcept : x(0.0f), y(0.0f) {}


	// 생성자입니다.
	// 
	// @param InX - 2치원 벡터의 첫 번째 성분입니다.
	// @param InY - 2차원 벡터의 두 번째 성분입니다.
	Vec2f(float InX, float InY) noexcept : x(InX), y(InY) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 2차원 벡터입니다.
	Vec2f(const Vec2f& InV) noexcept : x(InV.x), y(InV.y) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 2차원 벡터입니다.
	Vec2f(Vec2f&& InV) noexcept : x(InV.x), y(InV.y) {}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 2차원 벡터입니다.
	Vec2f& operator=(const Vec2f& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;

		return *this;
	}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 2차원 벡터입니다.
	Vec2f& operator=(Vec2f&& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;

		return *this;
	}


	// float 타입 2차원 벡터의 첫 번째 성분입니다.
	float x = 0.0f;


	// float 타입 2차원 벡터의 두 번째 성분입니다.
	float y = 0.0f;
};


// int32_t 타입의 3차원 벡터입니다.
struct Vec3i
{
	// 생성자입니다.
	Vec3i() noexcept : x(0), y(0), z(0) {}


	// 생성자입니다.
	// 
	// @param InX - 3치원 벡터의 첫 번째 성분입니다.
	// @param InY - 3차원 벡터의 두 번째 성분입니다.
	// @param InZ - 3차원 벡터의 세 번째 성분입니다.
	Vec3i(int32_t InX, int32_t InY, int32_t InZ) noexcept : x(InX), y(InY), z(InZ) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 3차원 벡터입니다.
	Vec3i(const Vec3i& InV) noexcept : x(InV.x), y(InV.y), z(InV.z) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 3차원 벡터입니다.
	Vec3i(Vec3i&& InV) noexcept : x(InV.x), y(InV.y), z(InV.z) {}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 3차원 벡터입니다.
	Vec3i& operator=(const Vec3i& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;
		z = InV.z;

		return *this;
	}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 3차원 벡터입니다.
	Vec3i& operator=(Vec3i&& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;
		z = InV.z;

		return *this;
	}


	// int32_t 타입 3차원 벡터의 첫 번째 성분입니다.
	int32_t x = 0;


	// int32_t 타입 3차원 벡터의 두 번째 성분입니다.
	int32_t y = 0;


	// int32_t 타입의 3차원 벡터의 세 번째 성분입니다.
	int32_t z = 0;
};


// float 타입의 3차원 벡터입니다.
struct Vec3f
{
	// 생성자입니다.
	Vec3f() noexcept : x(0.0f), y(0.0f), z(0.0f) {}


	// 생성자입니다.
	// 
	// @param InX - 3치원 벡터의 첫 번째 성분입니다.
	// @param InY - 3차원 벡터의 두 번째 성분입니다.
	// @param InZ - 3차원 벡터의 세 번째 성분입니다.
	Vec3f(float InX, float InY, float InZ) noexcept : x(InX), y(InY), z(InZ) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 3차원 벡터입니다.
	Vec3f(const Vec3f& InV) noexcept : x(InV.x), y(InV.y), z(InV.z) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 3차원 벡터입니다.
	Vec3f(Vec3f&& InV) noexcept : x(InV.x), y(InV.y), z(InV.z) {}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 3차원 벡터입니다.
	Vec3f& operator=(const Vec3f& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;
		z = InV.z;

		return *this;
	}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 3차원 벡터입니다.
	Vec3f& operator=(Vec3f&& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;
		z = InV.z;

		return *this;
	}


	// float 타입 3차원 벡터의 첫 번째 성분입니다.
	float x = 0.0f;


	// float 타입 3차원 벡터의 두 번째 성분입니다.
	float y = 0.0f;


	// float 타입 3차원 벡터의 세 번째 성분입니다.
	float z = 0.0f;
};


// int32_t 타입의 4차원 벡터입니다.
struct Vec4i
{
	// 생성자입니다.
	Vec4i() noexcept : x(0), y(0), z(0), w(0) {}


	// 생성자입니다.
	// 
	// @param InX - 4치원 벡터의 첫 번째 성분입니다.
	// @param InY - 4차원 벡터의 두 번째 성분입니다.
	// @param InZ - 4차원 벡터의 세 번째 성분입니다.
	// @param InW - 4차원 벡터의 네 번째 성분입니다.
	Vec4i(int32_t InX, int32_t InY, int32_t InZ, int32_t InW) noexcept : x(InX), y(InY), z(InZ), w(InW) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 4차원 벡터입니다.
	Vec4i(const Vec4i& InV) noexcept : x(InV.x), y(InV.y), z(InV.z), w(InV.w) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 4차원 벡터입니다.
	Vec4i(Vec4i&& InV) noexcept : x(InV.x), y(InV.y), z(InV.z), w(InV.w) {}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 4차원 벡터입니다.
	Vec4i& operator=(const Vec4i& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;
		z = InV.z;
		w = InV.w;

		return *this;
	}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 4차원 벡터입니다.
	Vec4i& operator=(Vec4i&& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;
		z = InV.z;
		w = InV.w;

		return *this;
	}


	// int32_t 타입 4차원 벡터의 첫 번째 성분입니다.
	int32_t x = 0;


	// int32_t 타입 4차원 벡터의 두 번째 성분입니다.
	int32_t y = 0;


	// int32_t 타입의 4차원 벡터의 세 번째 성분입니다.
	int32_t z = 0;


	// int32_t 타입의 4차원 벡터의 네 번째 성분입니다.
	int32_t w = 0;
};


// float 타입의 4차원 벡터입니다.
struct Vec4f
{
	// 생성자입니다.
	Vec4f() noexcept : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}


	// 생성자입니다.
	// 
	// @param InX - 4치원 벡터의 첫 번째 성분입니다.
	// @param InY - 4차원 벡터의 두 번째 성분입니다.
	// @param InZ - 4차원 벡터의 세 번째 성분입니다.
	// @param InW - 4차원 벡터의 네 번째 성분입니다.
	Vec4f(float InX, float InY, float InZ, float InW) noexcept : x(InX), y(InY), z(InZ), w(InW) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 4차원 벡터입니다.
	Vec4f(const Vec4f& InV) noexcept : x(InV.x), y(InV.y), z(InV.z), w(InV.w) {}


	// 복사 생성자입니다.
	//
	// @param InV - 복사를 수행할 4차원 벡터입니다.
	Vec4f(Vec4f&& InV) noexcept : x(InV.x), y(InV.y), z(InV.z), w(InV.w) {}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 4차원 벡터입니다.
	Vec4f& operator=(const Vec4f& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;
		z = InV.z;
		w = InV.w;

		return *this;
	}


	// 대입 연산자입니다.
	//
	// @param InV - 복사를 수행할 4차원 벡터입니다.
	Vec4f& operator=(Vec4f&& InV) noexcept
	{
		if (this == &InV) return *this;

		x = InV.x;
		y = InV.y;
		z = InV.z;
		w = InV.w;

		return *this;
	}


	// float 타입 4차원 벡터의 첫 번째 성분입니다.
	float x = 0.0f;


	// float 타입 4차원 벡터의 두 번째 성분입니다.
	float y = 0.0f;


	// float 타입 4차원 벡터의 세 번째 성분입니다.
	float z = 0.0f;


	// float 타입의 4차원 벡터의 네 번째 성분입니다.
	float w = 0.0f;
};


// Vec2i의 덧셈 연산입니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec2i operator+(const Vec2i& InLhs, const Vec2i& InRhs);


// Vec2i의 뺄셈 연산입니다.
//
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 뺀 결과를 반환합니다.
Vec2i operator-(const Vec2i& InLhs, const Vec2i& InRhs);


// Vec2i의 곱셈 연산입니다.
// 이때, 두 벡터의 곱셈은 각 원소를 곱하는 연산입니다.
// 내적 연산의 경우, Dot 함수를 통해 사용가능합니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec2i operator*(const Vec2i& InLhs, const Vec2i& InRhs);


// Vec2i 의 Scale 연산입니다.
// 
// @param InVec2i - Scale 연산을 수행할 벡터입니다.
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec2i operator*(const Vec2i& InVec2i, const int32_t& InScale);


// Vec2i 의 Scale 연산입니다.
//
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @param InVec2i - Scale 연산을 수행할 벡터입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec2i operator*(const int32_t& InScale, const Vec2i& InVec2i);


// Vec2f의 덧셈 연산입니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec2f operator+(const Vec2f& InLhs, const Vec2f& InRhs);


// Vec2f의 뺄셈 연산입니다.
//
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 뺀 결과를 반환합니다.
Vec2f operator-(const Vec2f& InLhs, const Vec2f& InRhs);


// Vec2f의 곱셈 연산입니다.
// 이때, 두 벡터의 곱셈은 각 원소를 곱하는 연산입니다.
// 내적 연산의 경우, Dot 함수를 통해 사용가능합니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec2f operator*(const Vec2f& InLhs, const Vec2f& InRhs);


// Vec2f 의 Scale 연산입니다.
// 
// @param InVec2f - Scale 연산을 수행할 벡터입니다.
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec2f operator*(const Vec2f& InVec2f, const float& InScale);


// Vec2f 의 Scale 연산입니다.
//
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @param InVec2f - Scale 연산을 수행할 벡터입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec2f operator*(const float& InScale, const Vec2f& InVec2f);


// Vec3i의 덧셈 연산입니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec3i operator+(const Vec3i& InLhs, const Vec3i& InRhs);


// Vec3i의 뺄셈 연산입니다.
//
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 뺀 결과를 반환합니다.
Vec3i operator-(const Vec3i& InLhs, const Vec3i& InRhs);


// Vec3i의 곱셈 연산입니다.
// 이때, 두 벡터의 곱셈은 각 원소를 곱하는 연산입니다.
// 내적 연산의 경우, Dot 함수를 통해 사용가능합니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec3i operator*(const Vec3i& InLhs, const Vec3i& InRhs);


// Vec3i 의 Scale 연산입니다.
// 
// @param InVec3i - Scale 연산을 수행할 벡터입니다.
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec3i operator*(const Vec3i& InVec3i, const int32_t& InScale);


// Vec3i 의 Scale 연산입니다.
//
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @param InVec3i - Scale 연산을 수행할 벡터입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec3i operator*(const int32_t& InScale, const Vec3i& InVec3i);


// Vec3f의 덧셈 연산입니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec3f operator+(const Vec3f& InLhs, const Vec3f& InRhs);


// Vec3f의 뺄셈 연산입니다.
//
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 뺀 결과를 반환합니다.
Vec3f operator-(const Vec3f& InLhs, const Vec3f& InRhs);


// Vec3f의 곱셈 연산입니다.
// 이때, 두 벡터의 곱셈은 각 원소를 곱하는 연산입니다.
// 내적 연산의 경우, Dot 함수를 통해 사용가능합니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec3f operator*(const Vec3f& InLhs, const Vec3f& InRhs);


// Vec3f 의 Scale 연산입니다.
// 
// @param InVec3f - Scale 연산을 수행할 벡터입니다.
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec3f operator*(const Vec3f& InVec3f, const float& InScale);


// Vec3f 의 Scale 연산입니다.
//
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @param InVec3f - Scale 연산을 수행할 벡터입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec3f operator*(const float& InScale, const Vec3f& InVec3f);


// Vec4i의 덧셈 연산입니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec4i operator+(const Vec4i& InLhs, const Vec4i& InRhs);


// Vec4i의 뺄셈 연산입니다.
//
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 뺀 결과를 반환합니다.
Vec4i operator-(const Vec4i& InLhs, const Vec4i& InRhs);


// Vec4i의 곱셈 연산입니다.
// 이때, 두 벡터의 곱셈은 각 원소를 곱하는 연산입니다.
// 내적 연산의 경우, Dot 함수를 통해 사용가능합니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec4i operator*(const Vec4i& InLhs, const Vec4i& InRhs);


// Vec4i 의 Scale 연산입니다.
// 
// @param InVec4i - Scale 연산을 수행할 벡터입니다.
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec4i operator*(const Vec4i& InVec4i, const int32_t& InScale);


// Vec4i 의 Scale 연산입니다.
//
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @param InVec4i - Scale 연산을 수행할 벡터입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec4i operator*(const int32_t& InScale, const Vec4i& InVec4i);


// Vec4f의 덧셈 연산입니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec4f operator+(const Vec4f& InLhs, const Vec4f& InRhs);


// Vec4f의 뺄셈 연산입니다.
//
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 뺀 결과를 반환합니다.
Vec4f operator-(const Vec4f& InLhs, const Vec4f& InRhs);


// Vec4f의 곱셈 연산입니다.
// 이때, 두 벡터의 곱셈은 각 원소를 곱하는 연산입니다.
// 내적 연산의 경우, Dot 함수를 통해 사용가능합니다.
// 
// @param InLhs - 덧셈 연산을 수행할 때 왼쪽 피연산자입니다.
// @param InRhs - 덧셈 연산을 수행할 때 오른쪽 피연산자입니다.
// @return - 두 벡터 각각의 원소의 더한 결과를 반환합니다.
Vec4f operator*(const Vec4f& InLhs, const Vec4f& InRhs);


// Vec4f 의 Scale 연산입니다.
// 
// @param InVec4f - Scale 연산을 수행할 벡터입니다.
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec4f operator*(const Vec4f& InVec4f, const float& InScale);


// Vec4f 의 Scale 연산입니다.
//
// @param InScale - 벡터의 원소에 크기 변환을 수행할 값입니다.
// @param InVec4f - Scale 연산을 수행할 벡터입니다.
// @return - 두 벡터 각각의 원소에 크기 변환을 수행한 벡터를 반환합니다.
Vec4f operator*(const float& InScale, const Vec4f& InVec4f);