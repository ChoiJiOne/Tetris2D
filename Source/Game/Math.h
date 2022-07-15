#pragma once

#include <cstdint>
#include <chrono>
#include <random>


namespace Game
{
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


	// 수학 관련 유틸리티 클래스입니다.
	class Math
	{
	public:
		// 임의의 정수를 생성합니다.
		//
		// @param InMinValue - 생성할 난수 범위의 최솟값입니다.
		// @param InMaxValue - 생성할 난수 범위의 최댓값입니다.
		// @return - 생성된 정수를 반환합니다.
		template <typename T>
		inline static int32_t GenerateRandomInt(T InMinValue, T InMaxValue)
		{
			if (InMinValue > InMaxValue)
			{
				std::swap(InMinValue, InMaxValue);
			}

			std::random_device RandomDevice;
			std::mt19937 Generator(RandomDevice());
			std::uniform_int_distribution<T> Distribution(InMinValue, InMaxValue);

			return Distribution(Generator);
		}


		// 임의의 실수를 생성합니다.
		//
		// @param InMinValue - 생성할 난수 범위의 최솟값입니다.
		// @param InMaxValue - 생성할 난수 범위의 최댓값입니다.
		// @return - 생성된 난수를 반환합니다.
		template <typename T>
		inline static float GenerateRandomFloat(T InMinValue, T InMaxValue)
		{
			if (InMinValue > InMaxValue)
			{
				std::swap(InMinValue, InMaxValue);
			}

			std::random_device RandomDevice;
			std::mt19937 Generator(RandomDevice());
			std::uniform_real_distribution<T> Distribution(InMinValue, InMaxValue);

			return Distribution(Generator);
		}


		// 입력 받은 값을 특정 범위의 값으로 자릅니다.
		//
		// @param InValue - 범위 내로 자르고자 하는 값입니다.
		// @param InMinValue - 범위의 최솟값입니다.
		// @param InMaxValue - 범위의 최댓값입니다.
		// @return - 범위 내의 값으로 자른 값을 반환합니다.
		template <typename T>
		inline static T Clamp(T InValue, T InMinValue, T InMaxValue)
		{
			if (InMinValue > InMaxValue)
			{
				std::swap(InMinValue, InMaxValue);
			}

			if (InValue < InMinValue)
			{
				return InMinValue;
			}
			else if (InValue > InMaxValue)
			{
				return InMaxValue;
			}
			else
			{
				return InValue;
			}
		}


		// 2차원 윈도우 float 좌표를 윈도우 pixel 좌표로 변환합니다.
		// https://www.realtimerendering.com/blog/the-center-of-the-pixel-is-0-50-5/
		// 
		// @param InPosition - 윈도우 float 좌표입니다.
		// @return - 변환된 윈도우 pixel 좌표입니다.
		inline static Vec2i ConvertPixelCoordinate(const Vec2f& InPosition)
		{
			return Vec2i(
				static_cast<int32_t>(InPosition.x + 0.5f),
				static_cast<int32_t>(InPosition.y + 0.5f)
			);
		}


		// 두 값을 선형 보간합니다.
		// 
		// @param InFirst - 보간을 수행할 두 값의 시작점입니다.
		// @param InLast - 보간을 수행할 두 값의 끝점입니다.
		// @param InAlpha - 두 값의 보간 비율입니다. 이때, 범위는 0 ~ 1입니다.
		// @return - 입력받은 두 값의 선형 보간값을 반환합니다.
		template<typename T>
		inline static T Lerp(const T& InFirst, const T& InLast, float InAlpha)
		{
			InAlpha = Clamp<float>(InAlpha, 0.0f, 1.0f);
			return (InFirst * (1.0f - InAlpha)) + (InLast * InAlpha);
		}


		// 두 벡터의 내적 연산을 수행합니다.
		// 
		// @param InLhs - 내적 연산을 수행할 때 왼쪽 피연산자입니다.
		// @param InRhs - 내적 연산을 수행할 때 오른쪽 피연산자입니다.
		// @return - 두 벡터 내적 결과를 반환합니다.
		inline static int32_t Dot(const Vec2i& InLhs, const Vec2i& InRhs)
		{
			return (InLhs.x * InRhs.x) + (InLhs.y * InRhs.y);
		}


		// 두 벡터의 내적 연산을 수행합니다.
		// 
		// @param InLhs - 내적 연산을 수행할 때 왼쪽 피연산자입니다.
		// @param InRhs - 내적 연산을 수행할 때 오른쪽 피연산자입니다.
		// @return - 두 벡터 내적 결과를 반환합니다.
		inline static float Dot(const Vec2f& InLhs, const Vec2f& InRhs)
		{
			return (InLhs.x * InRhs.x) + (InLhs.y * InRhs.y);
		}


		// 두 벡터의 내적 연산을 수행합니다.
		// 
		// @param InLhs - 내적 연산을 수행할 때 왼쪽 피연산자입니다.
		// @param InRhs - 내적 연산을 수행할 때 오른쪽 피연산자입니다.
		// @return - 두 벡터 내적 결과를 반환합니다.
		inline static int32_t Dot(const Vec3i& InLhs, const Vec3i& InRhs)
		{
			return (InLhs.x * InRhs.x) + (InLhs.y * InRhs.y) + (InLhs.z * InRhs.z);
		}


		// 두 벡터의 내적 연산을 수행합니다.
		// 
		// @param InLhs - 내적 연산을 수행할 때 왼쪽 피연산자입니다.
		// @param InRhs - 내적 연산을 수행할 때 오른쪽 피연산자입니다.
		// @return - 두 벡터 내적 결과를 반환합니다.
		inline static float Dot(const Vec3f& InLhs, const Vec3f& InRhs)
		{
			return (InLhs.x * InRhs.x) + (InLhs.y * InRhs.y) + (InLhs.z * InRhs.z);
		}


		// 두 벡터의 내적 연산을 수행합니다.
		// 
		// @param InLhs - 내적 연산을 수행할 때 왼쪽 피연산자입니다.
		// @param InRhs - 내적 연산을 수행할 때 오른쪽 피연산자입니다.
		// @return - 두 벡터 내적 결과를 반환합니다.
		inline static int32_t Dot(const Vec4i& InLhs, const Vec4i& InRhs)
		{
			return (InLhs.x * InRhs.x) + (InLhs.y * InRhs.y) + (InLhs.z * InRhs.z) + (InLhs.w * InRhs.w);
		}


		// 두 벡터의 내적 연산을 수행합니다.
		// 
		// @param InLhs - 내적 연산을 수행할 때 왼쪽 피연산자입니다.
		// @param InRhs - 내적 연산을 수행할 때 오른쪽 피연산자입니다.
		// @return - 두 벡터 내적 결과를 반환합니다.
		inline static float Dot(const Vec4f& InLhs, const Vec4f& InRhs)
		{
			return (InLhs.x * InRhs.x) + (InLhs.y * InRhs.y) + (InLhs.z * InRhs.z) + (InLhs.w * InRhs.w);
		}
	};


	// 32bit 압축 RGBA 색상을 정의합니다.
	using RGBA32 = uint32_t;


	// 선형 색상을 정의합니다.
	using LinearColor = Vec4f;


	// 색상을 관리하는 클래스입니다.
	class Color
	{
	public:
		static LinearColor Black;
		static LinearColor Red;
		static LinearColor Green;
		static LinearColor Blue;
		static LinearColor Yellow;
		static LinearColor Magenta;
		static LinearColor Cyan;
		static LinearColor White;


		// R8, G8, B8, A8 값을 RGBA32로 변환합니다.
		// 
		// @param InRed - 색상 변환을 수행할 R값입니다.
		// @param InGreen - 색상 변환을 수행할 G값입니다.
		// @param InBlue - 색상 변환을 수행할 B값입니다.
		// @param InAlpha - 색상 변환을 수행할 A값입니다.
		// @return - 변환된 RGBA32를 반환합니다.
		inline static RGBA32 ConvertR8G8B8A8ToRGBA32(uint8_t InRed, uint8_t InGreen, uint8_t InBlue, uint8_t InAlpha)
		{
			return (InAlpha << 24) + (InBlue << 16) + (InGreen << 8) + (InRed << 0);
		}


		// R8, G8, B8, A8 값을 LinearColor로 변환합니다.
		// 
		// @param InRed - 색상 변환을 수행할 R값입니다.
		// @param InGreen - 색상 변환을 수행할 G값입니다.
		// @param InBlue - 색상 변환을 수행할 B값입니다.
		// @param InAlpha - 색상 변환을 수행할 A값입니다.
		// @return - 변환된 LinearColor를 반환합니다.
		inline static LinearColor ConvertR8G8B8A8ToLinearColor(uint8_t InRed, uint8_t InGreen, uint8_t InBlue, uint8_t InAlpha)
		{
			return LinearColor(
				Math::Clamp<float>(static_cast<float>(InRed) / 255.0f, 0.0f, 1.0f),
				Math::Clamp<float>(static_cast<float>(InGreen) / 255.0f, 0.0f, 1.0f),
				Math::Clamp<float>(static_cast<float>(InBlue) / 255.0f, 0.0f, 1.0f),
				Math::Clamp<float>(static_cast<float>(InAlpha) / 255.0f, 0.0f, 1.0f)
			);
		}


		// RGBA32 값을 R8G8B8A8 값으로 변환합니다.
		// 
		// @param InRGBA32 - 변환을 수행할 RGBA 값입니다.
		// @param OutRed - 변환이 완료된 R값입니다.
		// @param OutGreen - 변환이 완료된 G값입니다.
		// @param OutBlue - 변환이 완료된 B값입니다.
		// @param OutAlpha - 변환이 완료된 A값입니다.
		inline static void ConvertRGBA32ToR8G8B8A8(const RGBA32& InRGBA32, uint8_t& OutRed, uint8_t& OutGreen, uint8_t& OutBlue, uint8_t& OutAlpha)
		{
			OutRed = (InRGBA32 >> 0) & 255;
			OutGreen = (InRGBA32 >> 8) & 255;
			OutBlue = (InRGBA32 >> 16) & 255;
			OutAlpha = (InRGBA32 >> 24) & 255;
		}


		// RGBA32 값을 LinearColor 값으로 변환합니다.
		// 
		// @param InRGBA32 - 변환을 수행할 RGBA 값입니다.
		// @return - 변환이 완료된 LinearColor 값입니다.
		inline static LinearColor ConvertRGBA32ToLinearColor(const RGBA32& InRGBA32)
		{
			uint8_t R = 0, G = 0, B = 0, A = 0;
			ConvertRGBA32ToR8G8B8A8(InRGBA32, R, G, B, A);
			return ConvertR8G8B8A8ToLinearColor(R, G, B, A);
		}


		// LinearColor 값을 R8G8B8A8 값으로 변환합니다.
		// 
		// @param InColor - 변환을 수행할 LinearColor 입니다.
		// @param OutRed - 변환이 완료된 R값입니다.
		// @param OutGreen - 변환이 완료된 G값입니다.
		// @param OutBlue - 변환이 완료된 B값입니다.
		// @param OutAlpha - 변환이 완료된 A값입니다.
		inline static void ConvertLinearColorToR8G8B8A8(const LinearColor& InColor, uint8_t& OutRed, uint8_t& OutGreen, uint8_t& OutBlue, uint8_t& OutAlpha)
		{
			OutRed = static_cast<uint8_t>(Math::Clamp<float>(InColor.x, 0.0f, 1.0f) * 255.0f);
			OutGreen = static_cast<uint8_t>(Math::Clamp<float>(InColor.y, 0.0f, 1.0f) * 255.0f);
			OutBlue = static_cast<uint8_t>(Math::Clamp<float>(InColor.z, 0.0f, 1.0f) * 255.0f);
			OutAlpha = static_cast<uint8_t>(Math::Clamp<float>(InColor.w, 0.0f, 1.0f) * 255.0f);
		}


		// LinearColor 값을 RGBA32 값으로 변환합니다.
		//
		// @param InColor - 변환을 수행할 LinearColor 입니다.
		// @return - 변환이 완료된 RGBA32 값입니다.
		inline static RGBA32 ConvertLinearColorToRGBA32(const LinearColor& InColor)
		{
			uint8_t R = 0, G = 0, B = 0, A = 0;
			ConvertLinearColorToR8G8B8A8(InColor, R, G, B, A);
			return ConvertR8G8B8A8ToRGBA32(R, G, B, A);
		}
	};
}