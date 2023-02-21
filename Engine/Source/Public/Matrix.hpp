#pragma once

#include <cmath>
#include <cstdint>
#include <algorithm>


/**
 * @brief 템플릿 기반의 2x2 행렬입니다.
 */
template <typename T>
struct Matrix2x2
{
	/**
	 * @brief 행렬의 기본 생성자입니다.
	 * 
	 * @note 모든 원소의 값을 0으로 초기화합니다.
	 */
	Matrix2x2() noexcept
	{
		m[0][0] = static_cast<T>(0); m[0][1] = static_cast<T>(0);
		m[1][0] = static_cast<T>(0); m[1][1] = static_cast<T>(0);
	}


	/**
	 * @brief 행렬의 생성자입니다.
	 * 
	 * @param m00 행렬의 (0, 0) 성분입니다.
	 * @param m01 행렬의 (0, 1) 성분입니다.
	 * @param m10 행렬의 (1, 0) 성분입니다.
	 * @param m11 행렬의 (1, 1) 성분입니다.
	 */
	Matrix2x2(
		T&& m00, T&& m01,
		T&& m10, T&& m11
	)
	{
		m[0][0] = m00; m[0][1] = m01;
		m[1][0] = m10; m[1][1] = m11;
	}


	/**
	 * @brief 행렬의 생성자입니다.
	 *
	 * @param m00 행렬의 (0, 0) 성분입니다.
	 * @param m01 행렬의 (0, 1) 성분입니다.
	 * @param m10 행렬의 (1, 0) 성분입니다.
	 * @param m11 행렬의 (1, 1) 성분입니다.
	 */
	Matrix2x2(
		const T& m00, const T& m01,
		const T& m10, const T& m11
	)
	{
		m[0][0] = m00; m[0][1] = m01;
		m[1][0] = m10; m[1][1] = m11;
	}


	/**
	 * @brief 행렬의 원소를 하나의 값으로 초기화합니다.
	 * 
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Matrix2x2(T&& Element) noexcept
	{
		m[0][0] = Element; m[0][1] = Element;
		m[1][0] = Element; m[1][1] = Element;
	}


	/**
	 * @brief 행렬의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Matrix2x2(const T& Element) noexcept
	{
		m[0][0] = Element; m[0][1] = Element;
		m[1][0] = Element; m[1][1] = Element;
	}


	/**
	 * @brief 행렬의 복사 생성자입니다.
	 * 
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 */
	Matrix2x2(Matrix2x2<T>&& Instance) noexcept
	{
		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1];
	}


	/**
	 * @brief 행렬의 복사 생성자입니다.
	 *
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 */
	Matrix2x2(const Matrix2x2<T>& Instance) noexcept
	{
		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1];
	}


	/**
	 * @brief 행렬의 대입 연산자입니다.
	 * 
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 * 
	 * @return 대입한 행렬의 참조자를 반환합니다.
	 */
	Matrix2x2<T>& operator=(Matrix2x2<T>&& Instance) noexcept
	{
		if (this == &Instance) return *this;

		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1];

		return *this;
	}


	/**
	 * @brief 행렬의 대입 연산자입니다.
	 *
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 *
	 * @return 대입한 행렬의 참조자를 반환합니다.
	 */
	Matrix2x2<T>& operator=(const Matrix2x2<T>& Instance) noexcept
	{
		if (this == &Instance) return *this;

		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1];

		return *this;
	}

	
	/**
	 * @brief 행렬의 모든 원소에 - 부호를 취합니다.
	 * 
	 * @return 모든 원소에 - 부호를 취한 새로운 행렬을 반환합니다.
	 */
	Matrix2x2<T> operator-() const
	{
		return Matrix2x2<T>(
			-m[0][0], -m[0][1],
			-m[1][0], -m[1][1]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 더합니다.
	 * 
	 * @param Instance 행렬의 덧셈을 수행할 피연산자입니다.
	 * 
	 * @return 두 행렬의 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Matrix2x2<T> operator+(Matrix2x2<T>&& Instance)
	{
		return Matrix2x2<T>(
			m[0][0] + Instance.m[0][0], m[0][1] + Instance.m[0][1],
			m[1][0] + Instance.m[1][0], m[1][1] + Instance.m[1][1]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 더합니다.
	 *
	 * @param Instance 행렬의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Matrix2x2<T> operator+(const Matrix2x2<T>& Instance)
	{
		return Matrix2x2<T>(
			m[0][0] + Instance.m[0][0], m[0][1] + Instance.m[0][1],
			m[1][0] + Instance.m[1][0], m[1][1] + Instance.m[1][1]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 행렬의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Matrix2x2<T> operator-(Matrix2x2<T>&& Instance)
	{
		return Matrix2x2<T>(
			m[0][0] - Instance.m[0][0], m[0][1] - Instance.m[0][1],
			m[1][0] - Instance.m[1][0], m[1][1] - Instance.m[1][1]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 행렬의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Matrix2x2<T> operator-(const Matrix2x2<T>& Instance)
	{
		return Matrix2x2<T>(
			m[0][0] - Instance.m[0][0], m[0][1] - Instance.m[0][1],
			m[1][0] - Instance.m[1][0], m[1][1] - Instance.m[1][1]
		);
	}


	/**
	 * @brief 두 행렬을 곱합니다.
	 * 
	 * @param Instance 행렬의 곱셈을 수행할 피연산자입니다.
	 * 
	 * @return 두 행렬을 곱한 결과를 반환합니다.
	 */
	Matrix2x2<T> operator*(Matrix2x2<T>&& Instance)
	{
		return Matrix2x2(
			m[0][0] * Instance.m[0][0] + m[0][1] * Instance.m[1][0], 
			m[0][0] * Instance.m[0][1] + m[0][1] * Instance.m[1][1],
			m[1][0] * Instance.m[0][0] + m[1][1] * Instance.m[1][0],
			m[1][0] * Instance.m[0][1] + m[1][1] * Instance.m[1][1]
		);
	}


	/**
	 * @brief 두 행렬을 곱합니다.
	 *
	 * @param Instance 행렬의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬을 곱한 결과를 반환합니다.
	 */
	Matrix2x2<T> operator*(const Matrix2x2<T>& Instance)
	{
		return Matrix2x2(
			m[0][0] * Instance.m[0][0] + m[0][1] * Instance.m[1][0],
			m[0][0] * Instance.m[0][1] + m[0][1] * Instance.m[1][1],
			m[1][0] * Instance.m[0][0] + m[1][1] * Instance.m[1][0],
			m[1][0] * Instance.m[0][1] + m[1][1] * Instance.m[1][1]
		);
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 더합니다.
	 * 
	 * @param Instance 연산을 수행할 피연산자입니다.
	 * 
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix2x2<T>& operator+=(Matrix2x2<T>&& Instance) noexcept
	{
		m[0][0] += Instance.m[0][0]; m[0][1] += Instance.m[0][1];
		m[1][0] += Instance.m[1][0]; m[1][1] += Instance.m[1][1];

		return *this;
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix2x2<T>& operator+=(const Matrix2x2<T>& Instance) noexcept
	{
		m[0][0] += Instance.m[0][0]; m[0][1] += Instance.m[0][1];
		m[1][0] += Instance.m[1][0]; m[1][1] += Instance.m[1][1];

		return *this;
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix2x2<T>& operator-=(Matrix2x2<T>&& Instance) noexcept
	{
		m[0][0] -= Instance.m[0][0]; m[0][1] -= Instance.m[0][1];
		m[1][0] -= Instance.m[1][0]; m[1][1] -= Instance.m[1][1];

		return *this;
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix2x2<T>& operator-=(const Matrix2x2<T>& Instance) noexcept
	{
		m[0][0] -= Instance.m[0][0]; m[0][1] -= Instance.m[0][1];
		m[1][0] -= Instance.m[1][0]; m[1][1] -= Instance.m[1][1];

		return *this;
	}


	/**
	 * @brief 두 행렬의 원소가 일치하는지 확인합니다.
	 * 
	 * @param Instance 일치하는지 확인할 행렬입니다.
	 * 
	 * @return 두 행렬의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(Matrix2x2<T>&& Instance) noexcept
	{
		return (m[0][0] == Instance.m[0][0])
			&& (m[0][1] == Instance.m[0][1])
			&& (m[1][0] == Instance.m[1][0])
			&& (m[1][1] == Instance.m[1][1]);
	}


	/**
	 * @brief 두 행렬의 원소가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 행렬입니다.
	 *
	 * @return 두 행렬의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(const Matrix2x2<T>& Instance) noexcept
	{
		return (m[0][0] == Instance.m[0][0])
			&& (m[0][1] == Instance.m[0][1])
			&& (m[1][0] == Instance.m[1][0])
			&& (m[1][1] == Instance.m[1][1]);
	}


	/**
	 * @brief 두 행렬의 원소가 일치하지 않는지 확인합니다.
	 * 
	 * @param 일치하지 않는지 확인할 피 연산자입니다.
	 * 
	 * @return 두 행렬의 원소가 일치하지 않으면 true, 일치하면 false를 반환합니다.
	 */
	bool operator!=(Matrix2x2<T>&& Instance) noexcept
	{
		return (m[0][0] != Instance.m[0][0])
			|| (m[0][1] != Instance.m[0][1])
			|| (m[1][0] != Instance.m[1][0])
			|| (m[1][1] != Instance.m[1][1]);
	}


	/**
	 * @brief 두 행렬의 원소가 일치하지 않는지 확인합니다.
	 *
	 * @param 일치하지 않는지 확인할 피 연산자입니다.
	 *
	 * @return 두 행렬의 원소가 일치하지 않으면 true, 일치하면 false를 반환합니다.
	 */
	bool operator!=(const Matrix2x2<T>& Instance) noexcept
	{
		return (m[0][0] != Instance.m[0][0])
			|| (m[0][1] != Instance.m[0][1])
			|| (m[1][0] != Instance.m[1][0])
			|| (m[1][1] != Instance.m[1][1]);
	}


	/**
	 * @brief 행렬을 단위 행렬로 설정합니다.
	 */
	void Identify()
	{
		m[0][0] = static_cast<T>(1); m[0][1] = static_cast<T>(0);
		m[1][0] = static_cast<T>(0); m[1][1] = static_cast<T>(1);
	}


	/**
	 * @brief 행렬의 원소입니다.
	 */
	T m[2][2];
};


/**
 * @brief 템플릿 기반의 3x3 행렬입니다.
 */
template <typename T>
struct Matrix3x3
{
	/**
	 * @brief 행렬의 기본 생성자입니다.
	 *
	 * @note 모든 원소의 값을 0으로 초기화합니다.
	 */
	Matrix3x3() noexcept
	{
		m[0][0] = static_cast<T>(0); m[0][1] = static_cast<T>(0); m[0][2] = static_cast<T>(0);
		m[1][0] = static_cast<T>(0); m[1][1] = static_cast<T>(0); m[1][2] = static_cast<T>(0);
		m[2][0] = static_cast<T>(0); m[2][1] = static_cast<T>(0); m[2][2] = static_cast<T>(0);
	}


	/**
	 * @brief 행렬의 생성자입니다.
	 *
	 * @param m00 행렬의 (0, 0) 성분입니다.
	 * @param m01 행렬의 (0, 1) 성분입니다.
	 * @param m02 행렬의 (0, 2) 성분입니다.
	 * @param m10 행렬의 (1, 0) 성분입니다.
	 * @param m11 행렬의 (1, 1) 성분입니다.
	 * @param m12 행렬의 (1, 2) 성분입니다.
	 * @param m20 행렬의 (2, 0) 성분입니다.
	 * @param m21 행렬의 (2, 1) 성분입니다.
	 * @param m22 행렬의 (2, 2) 성분입니다.
	 */
	Matrix3x3(
		T&& m00, T&& m01, T&& m02,
		T&& m10, T&& m11, T&& m12,
		T&& m20, T&& m21, T&& m22
	)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
	}


	/**
	 * @brief 행렬의 생성자입니다.
	 *
	 * @param m00 행렬의 (0, 0) 성분입니다.
	 * @param m01 행렬의 (0, 1) 성분입니다.
	 * @param m02 행렬의 (0, 2) 성분입니다.
	 * @param m10 행렬의 (1, 0) 성분입니다.
	 * @param m11 행렬의 (1, 1) 성분입니다.
	 * @param m12 행렬의 (1, 2) 성분입니다.
	 * @param m20 행렬의 (2, 0) 성분입니다.
	 * @param m21 행렬의 (2, 1) 성분입니다.
	 * @param m22 행렬의 (2, 2) 성분입니다.
	 */
	Matrix3x3(
		const T& m00, const T& m01, const T& m02,
		const T& m10, const T& m11, const T& m12,
		const T& m20, const T& m21, const T& m22
	)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
	}


	/**
	 * @brief 행렬의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Matrix3x3(T&& Element) noexcept
	{
		m[0][0] = Element; m[0][1] = Element; m[0][2] = Element;
		m[1][0] = Element; m[1][1] = Element; m[1][2] = Element;
		m[2][0] = Element; m[2][1] = Element; m[2][2] = Element;
	}


	/**
	 * @brief 행렬의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Matrix3x3(const T& Element) noexcept
	{
		m[0][0] = Element; m[0][1] = Element; m[0][2] = Element;
		m[1][0] = Element; m[1][1] = Element; m[1][2] = Element;
		m[2][0] = Element; m[2][1] = Element; m[2][2] = Element;
	}


	/**
	 * @brief 행렬의 복사 생성자입니다.
	 *
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 */
	Matrix3x3(Matrix3x3<T>&& Instance) noexcept
	{
		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1]; m[0][2] = Instance.m[0][2];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1]; m[1][2] = Instance.m[1][2];
		m[2][0] = Instance.m[2][0]; m[2][1] = Instance.m[2][1]; m[2][2] = Instance.m[2][2];
	}


	/**
	 * @brief 행렬의 복사 생성자입니다.
	 *
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 */
	Matrix3x3(const Matrix3x3<T>& Instance) noexcept
	{
		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1]; m[0][2] = Instance.m[0][2];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1]; m[1][2] = Instance.m[1][2];
		m[2][0] = Instance.m[2][0]; m[2][1] = Instance.m[2][1]; m[2][2] = Instance.m[2][2];
	}


	/**
	 * @brief 행렬의 대입 연산자입니다.
	 *
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 *
	 * @return 대입한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator=(Matrix3x3<T>&& Instance) noexcept
	{
		if (this == &Instance) return *this;

		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1]; m[0][2] = Instance.m[0][2];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1]; m[1][2] = Instance.m[1][2];
		m[2][0] = Instance.m[2][0]; m[2][1] = Instance.m[2][1]; m[2][2] = Instance.m[2][2];

		return *this;
	}


	/**
	 * @brief 행렬의 대입 연산자입니다.
	 *
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 *
	 * @return 대입한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator=(const Matrix3x3<T>& Instance) noexcept
	{
		if (this == &Instance) return *this;

		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1]; m[0][2] = Instance.m[0][2];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1]; m[1][2] = Instance.m[1][2];
		m[2][0] = Instance.m[2][0]; m[2][1] = Instance.m[2][1]; m[2][2] = Instance.m[2][2];

		return *this;
	}


	/**
	 * @brief 행렬의 모든 원소에 - 부호를 취합니다.
	 *
	 * @return 모든 원소에 - 부호를 취한 새로운 행렬을 반환합니다.
	 */
	Matrix3x3<T> operator-() const
	{
		return Matrix3x3<T>(
			-m[0][0], -m[0][1], -m[0][2],
			-m[1][0], -m[1][1], -m[1][2],
			-m[2][0], -m[2][1], -m[2][2]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 더합니다.
	 *
	 * @param Instance 행렬의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Matrix3x3<T> operator+(Matrix3x3<T>&& Instance)
	{
		return Matrix3x3<T>(
			m[0][0] + Instance.m[0][0], m[0][1] + Instance.m[0][1], m[0][2] + Instance.m[0][2],
			m[1][0] + Instance.m[1][0], m[1][1] + Instance.m[1][1], m[1][2] + Instance.m[1][2],
			m[2][0] + Instance.m[2][0], m[2][1] + Instance.m[2][1], m[2][2] + Instance.m[2][2]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 더합니다.
	 *
	 * @param Instance 행렬의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Matrix3x3<T> operator+(const Matrix3x3<T>& Instance)
	{
		return Matrix3x3<T>(
			m[0][0] + Instance.m[0][0], m[0][1] + Instance.m[0][1], m[0][2] + Instance.m[0][2],
			m[1][0] + Instance.m[1][0], m[1][1] + Instance.m[1][1], m[1][2] + Instance.m[1][2],
			m[2][0] + Instance.m[2][0], m[2][1] + Instance.m[2][1], m[2][2] + Instance.m[2][2]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 행렬의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Matrix3x3<T> operator-(Matrix3x3<T>&& Instance)
	{
		return Matrix3x3<T>(
			m[0][0] - Instance.m[0][0], m[0][1] - Instance.m[0][1], m[0][2] - Instance.m[0][2],
			m[1][0] - Instance.m[1][0], m[1][1] - Instance.m[1][1], m[1][2] - Instance.m[1][2],
			m[2][0] - Instance.m[2][0], m[2][1] - Instance.m[2][1], m[2][2] - Instance.m[2][2]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 행렬의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Matrix3x3<T> operator-(const Matrix3x3<T>& Instance)
	{
		return Matrix3x3<T>(
			m[0][0] - Instance.m[0][0], m[0][1] - Instance.m[0][1], m[0][2] - Instance.m[0][2],
			m[1][0] - Instance.m[1][0], m[1][1] - Instance.m[1][1], m[1][2] - Instance.m[1][2],
			m[2][0] - Instance.m[2][0], m[2][1] - Instance.m[2][1], m[2][2] - Instance.m[2][2]
		);
	}


	/**
	 * @brief 두 행렬을 곱합니다.
	 *
	 * @param Instance 행렬의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬을 곱한 결과를 반환합니다.
	 */
	Matrix3x3<T> operator*(Matrix3x3<T>&& Instance)
	{
		return Matrix3x3(
			m[0][0] * Instance.m[0][0] + m[0][1] * Instance.m[1][0] + m[0][2] * Instance.m[2][0],
			m[0][0] * Instance.m[0][1] + m[0][1] * Instance.m[1][1] + m[0][2] * Instance.m[2][1],
			m[0][0] * Instance.m[0][2] + m[0][1] * Instance.m[1][2] + m[0][2] * Instance.m[2][2],
			m[1][0] * Instance.m[0][0] + m[1][1] * Instance.m[1][0] + m[1][2] * Instance.m[2][0],
			m[1][0] * Instance.m[0][1] + m[1][1] * Instance.m[1][1] + m[1][2] * Instance.m[2][1],
			m[1][0] * Instance.m[0][2] + m[1][1] * Instance.m[1][2] + m[1][2] * Instance.m[2][2],
			m[2][0] * Instance.m[0][0] + m[2][1] * Instance.m[1][0] + m[2][2] * Instance.m[2][0],
			m[2][0] * Instance.m[0][1] + m[2][1] * Instance.m[1][1] + m[2][2] * Instance.m[2][1],
			m[2][0] * Instance.m[0][2] + m[2][1] * Instance.m[1][2] + m[2][2] * Instance.m[2][2],
		);
	}


	/**
	 * @brief 두 행렬을 곱합니다.
	 *
	 * @param Instance 행렬의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬을 곱한 결과를 반환합니다.
	 */
	Matrix3x3<T> operator*(const Matrix3x3<T>& Instance)
	{
		return Matrix3x3(
			m[0][0] * Instance.m[0][0] + m[0][1] * Instance.m[1][0] + m[0][2] * Instance.m[2][0],
			m[0][0] * Instance.m[0][1] + m[0][1] * Instance.m[1][1] + m[0][2] * Instance.m[2][1],
			m[0][0] * Instance.m[0][2] + m[0][1] * Instance.m[1][2] + m[0][2] * Instance.m[2][2],
			m[1][0] * Instance.m[0][0] + m[1][1] * Instance.m[1][0] + m[1][2] * Instance.m[2][0],
			m[1][0] * Instance.m[0][1] + m[1][1] * Instance.m[1][1] + m[1][2] * Instance.m[2][1],
			m[1][0] * Instance.m[0][2] + m[1][1] * Instance.m[1][2] + m[1][2] * Instance.m[2][2],
			m[2][0] * Instance.m[0][0] + m[2][1] * Instance.m[1][0] + m[2][2] * Instance.m[2][0],
			m[2][0] * Instance.m[0][1] + m[2][1] * Instance.m[1][1] + m[2][2] * Instance.m[2][1],
			m[2][0] * Instance.m[0][2] + m[2][1] * Instance.m[1][2] + m[2][2] * Instance.m[2][2],
		);
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator+=(Matrix3x3<T>&& Instance) noexcept
	{
		m[0][0] += Instance.m[0][0]; m[0][1] += Instance.m[0][1]; m[0][2] += Instance.m[0][2];
		m[1][0] += Instance.m[1][0]; m[1][1] += Instance.m[1][1]; m[1][2] += Instance.m[1][2];
		m[2][0] += Instance.m[2][0]; m[2][1] += Instance.m[2][1]; m[2][2] += Instance.m[2][2];

		return *this;
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator+=(const Matrix3x3<T>& Instance) noexcept
	{
		m[0][0] += Instance.m[0][0]; m[0][1] += Instance.m[0][1]; m[0][2] += Instance.m[0][2];
		m[1][0] += Instance.m[1][0]; m[1][1] += Instance.m[1][1]; m[1][2] += Instance.m[1][2];
		m[2][0] += Instance.m[2][0]; m[2][1] += Instance.m[2][1]; m[2][2] += Instance.m[2][2];

		return *this;
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator-=(Matrix3x3<T>&& Instance) noexcept
	{
		m[0][0] -= Instance.m[0][0]; m[0][1] -= Instance.m[0][1]; m[0][2] -= Instance.m[0][2];
		m[1][0] -= Instance.m[1][0]; m[1][1] -= Instance.m[1][1]; m[1][2] -= Instance.m[1][2];
		m[2][0] -= Instance.m[2][0]; m[2][1] -= Instance.m[2][1]; m[2][2] -= Instance.m[2][2];

		return *this;
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator-=(const Matrix3x3<T>& Instance) noexcept
	{
		m[0][0] -= Instance.m[0][0]; m[0][1] -= Instance.m[0][1]; m[0][2] -= Instance.m[0][2];
		m[1][0] -= Instance.m[1][0]; m[1][1] -= Instance.m[1][1]; m[1][2] -= Instance.m[1][2];
		m[2][0] -= Instance.m[2][0]; m[2][1] -= Instance.m[2][1]; m[2][2] -= Instance.m[2][2];

		return *this;
	}


	/**
	 * @brief 두 행렬의 원소가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 행렬입니다.
	 *
	 * @return 두 행렬의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(Matrix3x3<T>&& Instance) noexcept
	{
		return (m[0][0] == Instance.m[0][0])
			&& (m[0][1] == Instance.m[0][1])
			&& (m[0][2] == Instance.m[0][2])
			&& (m[1][0] == Instance.m[1][0])
			&& (m[1][1] == Instance.m[1][1])
			&& (m[1][2] == Instance.m[1][2])
			&& (m[2][0] == Instance.m[2][0])
			&& (m[2][1] == Instance.m[2][1])
			&& (m[2][2] == Instance.m[2][2]);
	}


	/**
	 * @brief 두 행렬의 원소가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 행렬입니다.
	 *
	 * @return 두 행렬의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(const Matrix3x3<T>& Instance) noexcept
	{
		return (m[0][0] == Instance.m[0][0])
			&& (m[0][1] == Instance.m[0][1])
			&& (m[0][2] == Instance.m[0][2])
			&& (m[1][0] == Instance.m[1][0])
			&& (m[1][1] == Instance.m[1][1])
			&& (m[1][2] == Instance.m[1][2])
			&& (m[2][0] == Instance.m[2][0])
			&& (m[2][1] == Instance.m[2][1])
			&& (m[2][2] == Instance.m[2][2]);
	}


	/**
	 * @brief 두 행렬의 원소가 일치하지 않는지 확인합니다.
	 *
	 * @param 일치하지 않는지 확인할 피 연산자입니다.
	 *
	 * @return 두 행렬의 원소가 일치하지 않으면 true, 일치하면 false를 반환합니다.
	 */
	bool operator!=(Matrix3x3<T>&& Instance) noexcept
	{
		return (m[0][0] != Instance.m[0][0])
			|| (m[0][1] != Instance.m[0][1])
			|| (m[0][2] != Instance.m[0][2])
			|| (m[1][0] != Instance.m[1][0])
			|| (m[1][1] != Instance.m[1][1])
			|| (m[1][2] != Instance.m[1][2])
			|| (m[2][0] != Instance.m[2][0])
			|| (m[2][1] != Instance.m[2][1])
			|| (m[2][2] != Instance.m[2][2]);
	}


	/**
	 * @brief 두 행렬의 원소가 일치하지 않는지 확인합니다.
	 *
	 * @param 일치하지 않는지 확인할 피 연산자입니다.
	 *
	 * @return 두 행렬의 원소가 일치하지 않으면 true, 일치하면 false를 반환합니다.
	 */
	bool operator!=(const Matrix3x3<T>& Instance) noexcept
	{
		return (m[0][0] != Instance.m[0][0])
			|| (m[0][1] != Instance.m[0][1])
			|| (m[0][2] != Instance.m[0][2])
			|| (m[1][0] != Instance.m[1][0])
			|| (m[1][1] != Instance.m[1][1])
			|| (m[1][2] != Instance.m[1][2])
			|| (m[2][0] != Instance.m[2][0])
			|| (m[2][1] != Instance.m[2][1])
			|| (m[2][2] != Instance.m[2][2]);
	}


	/**
	 * @brief 행렬을 단위 행렬로 설정합니다.
	 */
	void Identify()
	{
		m[0][0] = static_cast<T>(1); m[0][1] = static_cast<T>(0); m[0][2] = static_cast<T>(0);
		m[1][0] = static_cast<T>(0); m[1][1] = static_cast<T>(1); m[1][2] = static_cast<T>(0);
		m[2][0] = static_cast<T>(0); m[2][1] = static_cast<T>(0); m[2][2] = static_cast<T>(1);
	}


	/**
	 * @brief 행렬의 원소입니다.
	 */
	T m[3][3];
};


/**
 * @brief 템플릿 기반의 4x4 행렬입니다.
 */
template <typename T>
struct Matrix4x4
{
	/**
	 * @brief 행렬의 기본 생성자입니다.
	 *
	 * @note 모든 원소의 값을 0으로 초기화합니다.
	 */
	Matrix4x4() noexcept
	{
		m[0][0] = static_cast<T>(0); m[0][1] = static_cast<T>(0); m[0][2] = static_cast<T>(0); m[0][3] = static_cast<T>(0);
		m[1][0] = static_cast<T>(0); m[1][1] = static_cast<T>(0); m[1][2] = static_cast<T>(0); m[1][3] = static_cast<T>(0);
		m[2][0] = static_cast<T>(0); m[2][1] = static_cast<T>(0); m[2][2] = static_cast<T>(0); m[2][3] = static_cast<T>(0);
		m[3][0] = static_cast<T>(0); m[3][1] = static_cast<T>(0); m[3][2] = static_cast<T>(0); m[3][3] = static_cast<T>(0);
	}


	/**
	 * @brief 행렬의 생성자입니다.
	 *
	 * @param m00 행렬의 (0, 0) 성분입니다.
	 * @param m01 행렬의 (0, 1) 성분입니다.
	 * @param m02 행렬의 (0, 2) 성분입니다.
	 * @param m03 행렬의 (0, 3) 성분입니다.
	 * @param m10 행렬의 (1, 0) 성분입니다.
	 * @param m11 행렬의 (1, 1) 성분입니다.
	 * @param m12 행렬의 (1, 2) 성분입니다.
	 * @param m13 행렬의 (1, 3) 성분입니다.
	 * @param m20 행렬의 (2, 0) 성분입니다.
	 * @param m21 행렬의 (2, 1) 성분입니다.
	 * @param m22 행렬의 (2, 2) 성분입니다.
	 * @param m23 행렬의 (2, 3) 성분입니다.
	 * @param m30 행렬의 (3, 0) 성분입니다.
	 * @param m31 행렬의 (3, 1) 성분입니다.
	 * @param m32 행렬의 (3, 2) 성분입니다.
	 * @param m33 행렬의 (3, 3) 성분입니다.
	 */
	Matrix4x4(
		T&& m00, T&& m01, T&& m02, T&& m03,
		T&& m10, T&& m11, T&& m12, T&& m13,
		T&& m20, T&& m21, T&& m22, T&& m23,
		T&& m30, T&& m31, T&& m32, T&& m33
	)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}


	/**
	 * @brief 행렬의 생성자입니다.
	 *
	 * @param m00 행렬의 (0, 0) 성분입니다.
	 * @param m01 행렬의 (0, 1) 성분입니다.
	 * @param m02 행렬의 (0, 2) 성분입니다.
	 * @param m03 행렬의 (0, 3) 성분입니다.
	 * @param m10 행렬의 (1, 0) 성분입니다.
	 * @param m11 행렬의 (1, 1) 성분입니다.
	 * @param m12 행렬의 (1, 2) 성분입니다.
	 * @param m13 행렬의 (1, 3) 성분입니다.
	 * @param m20 행렬의 (2, 0) 성분입니다.
	 * @param m21 행렬의 (2, 1) 성분입니다.
	 * @param m22 행렬의 (2, 2) 성분입니다.
	 * @param m23 행렬의 (2, 3) 성분입니다.
	 * @param m30 행렬의 (3, 0) 성분입니다.
	 * @param m31 행렬의 (3, 1) 성분입니다.
	 * @param m32 행렬의 (3, 2) 성분입니다.
	 * @param m33 행렬의 (3, 3) 성분입니다.
	 */
	Matrix4x4(
		const T& m00, const T& m01, const T& m02, const T& m03,
		const T& m10, const T& m11, const T& m12, const T& m13,
		const T& m20, const T& m21, const T& m22, const T& m23,
		const T& m30, const T& m31, const T& m32, const T& m33
	)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}


	/**
	 * @brief 행렬의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Matrix4x4(T&& Element) noexcept
	{
		m[0][0] = Element; m[0][1] = Element; m[0][2] = Element; m[0][3] = Element;
		m[1][0] = Element; m[1][1] = Element; m[1][2] = Element; m[1][3] = Element;
		m[2][0] = Element; m[2][1] = Element; m[2][2] = Element; m[2][3] = Element;
		m[3][0] = Element; m[3][1] = Element; m[3][2] = Element; m[3][3] = Element;
	}


	/**
	 * @brief 행렬의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Matrix4x4(const T& Element) noexcept
	{
		m[0][0] = Element; m[0][1] = Element; m[0][2] = Element; m[0][3] = Element;
		m[1][0] = Element; m[1][1] = Element; m[1][2] = Element; m[1][3] = Element;
		m[2][0] = Element; m[2][1] = Element; m[2][2] = Element; m[2][3] = Element;
		m[3][0] = Element; m[3][1] = Element; m[3][2] = Element; m[3][3] = Element;
	}


	/**
	 * @brief 행렬의 복사 생성자입니다.
	 *
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 */
	Matrix4x4(Matrix4x4<T>&& Instance) noexcept
	{
		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1]; m[0][2] = Instance.m[0][2]; m[0][3] = Instance.m[0][3];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1]; m[1][2] = Instance.m[1][2]; m[1][3] = Instance.m[1][3];
		m[2][0] = Instance.m[2][0]; m[2][1] = Instance.m[2][1]; m[2][2] = Instance.m[2][2]; m[2][3] = Instance.m[2][3];
		m[3][0] = Instance.m[3][0]; m[3][1] = Instance.m[3][1]; m[3][2] = Instance.m[3][2]; m[3][3] = Instance.m[3][3];
	}


	/**
	 * @brief 행렬의 복사 생성자입니다.
	 *
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 */
	Matrix4x4(const Matrix4x4<T>& Instance) noexcept
	{
		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1]; m[0][2] = Instance.m[0][2]; m[0][3] = Instance.m[0][3];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1]; m[1][2] = Instance.m[1][2]; m[1][3] = Instance.m[1][3];
		m[2][0] = Instance.m[2][0]; m[2][1] = Instance.m[2][1]; m[2][2] = Instance.m[2][2]; m[2][3] = Instance.m[2][3];
		m[3][0] = Instance.m[3][0]; m[3][1] = Instance.m[3][1]; m[3][2] = Instance.m[3][2]; m[3][3] = Instance.m[3][3];
	}


	/**
	 * @brief 행렬의 대입 연산자입니다.
	 *
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 *
	 * @return 대입한 행렬의 참조자를 반환합니다.
	 */
	Matrix4x4<T>& operator=(Matrix4x4<T>&& Instance) noexcept
	{
		if (this == &Instance) return *this;

		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1]; m[0][2] = Instance.m[0][2]; m[0][3] = Instance.m[0][3];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1]; m[1][2] = Instance.m[1][2]; m[1][3] = Instance.m[1][3];
		m[2][0] = Instance.m[2][0]; m[2][1] = Instance.m[2][1]; m[2][2] = Instance.m[2][2]; m[2][3] = Instance.m[2][3];
		m[3][0] = Instance.m[3][0]; m[3][1] = Instance.m[3][1]; m[3][2] = Instance.m[3][2]; m[3][3] = Instance.m[3][3];

		return *this;
	}


	/**
	 * @brief 행렬의 대입 연산자입니다.
	 *
	 * @param Instance 원소를 복사할 행렬의 인스턴스입니다.
	 *
	 * @return 대입한 행렬의 참조자를 반환합니다.
	 */
	Matrix4x4<T>& operator=(const Matrix4x4<T>& Instance) noexcept
	{
		if (this == &Instance) return *this;

		m[0][0] = Instance.m[0][0]; m[0][1] = Instance.m[0][1]; m[0][2] = Instance.m[0][2]; m[0][3] = Instance.m[0][3];
		m[1][0] = Instance.m[1][0]; m[1][1] = Instance.m[1][1]; m[1][2] = Instance.m[1][2]; m[1][3] = Instance.m[1][3];
		m[2][0] = Instance.m[2][0]; m[2][1] = Instance.m[2][1]; m[2][2] = Instance.m[2][2]; m[2][3] = Instance.m[2][3];
		m[3][0] = Instance.m[3][0]; m[3][1] = Instance.m[3][1]; m[3][2] = Instance.m[3][2]; m[3][3] = Instance.m[3][3];

		return *this;
	}


	/**
	 * @brief 행렬의 모든 원소에 - 부호를 취합니다.
	 *
	 * @return 모든 원소에 - 부호를 취한 새로운 행렬을 반환합니다.
	 */
	Matrix4x4<T> operator-() const
	{
		return Matrix4x4<T>(
			-m[0][0], -m[0][1], -m[0][2], -m[0][3],
			-m[1][0], -m[1][1], -m[1][2], -m[1][3],
			-m[2][0], -m[2][1], -m[2][2], -m[2][3],
			-m[3][0], -m[3][1], -m[3][2], -m[3][3]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 더합니다.
	 *
	 * @param Instance 행렬의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Matrix4x4<T> operator+(Matrix4x4<T>&& Instance)
	{
		return Matrix4x4<T>(
			m[0][0] + Instance.m[0][0], m[0][1] + Instance.m[0][1], m[0][2] + Instance.m[0][2], m[0][3] + Instance.m[0][3],
			m[1][0] + Instance.m[1][0], m[1][1] + Instance.m[1][1], m[1][2] + Instance.m[1][2], m[1][3] + Instance.m[1][3],
			m[2][0] + Instance.m[2][0], m[2][1] + Instance.m[2][1], m[2][2] + Instance.m[2][2], m[2][3] + Instance.m[2][3],
			m[3][0] + Instance.m[3][0], m[3][1] + Instance.m[3][1], m[3][2] + Instance.m[3][2], m[3][3] + Instance.m[3][3]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 더합니다.
	 *
	 * @param Instance 행렬의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Matrix4x4<T> operator+(const Matrix4x4<T>& Instance)
	{
		return Matrix4x4<T>(
			m[0][0] + Instance.m[0][0], m[0][1] + Instance.m[0][1], m[0][2] + Instance.m[0][2], m[0][3] + Instance.m[0][3],
			m[1][0] + Instance.m[1][0], m[1][1] + Instance.m[1][1], m[1][2] + Instance.m[1][2], m[1][3] + Instance.m[1][3],
			m[2][0] + Instance.m[2][0], m[2][1] + Instance.m[2][1], m[2][2] + Instance.m[2][2], m[2][3] + Instance.m[2][3],
			m[3][0] + Instance.m[3][0], m[3][1] + Instance.m[3][1], m[3][2] + Instance.m[3][2], m[3][3] + Instance.m[3][3]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 행렬의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Matrix4x4<T> operator-(Matrix4x4<T>&& Instance)
	{
		return Matrix4x4<T>(
			m[0][0] - Instance.m[0][0], m[0][1] - Instance.m[0][1], m[0][2] - Instance.m[0][2], m[0][3] - Instance.m[0][3],
			m[1][0] - Instance.m[1][0], m[1][1] - Instance.m[1][1], m[1][2] - Instance.m[1][2], m[1][3] - Instance.m[1][3],
			m[2][0] - Instance.m[2][0], m[2][1] - Instance.m[2][1], m[2][2] - Instance.m[2][2], m[2][3] - Instance.m[2][3],
			m[3][0] - Instance.m[3][0], m[3][1] - Instance.m[3][1], m[3][2] - Instance.m[3][2], m[3][3] - Instance.m[3][3]
		);
	}


	/**
	 * @brief 두 행렬의 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 행렬의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Matrix4x4<T> operator-(const Matrix4x4<T>& Instance)
	{
		return Matrix4x4<T>(
			m[0][0] - Instance.m[0][0], m[0][1] - Instance.m[0][1], m[0][2] - Instance.m[0][2], m[0][3] - Instance.m[0][3],
			m[1][0] - Instance.m[1][0], m[1][1] - Instance.m[1][1], m[1][2] - Instance.m[1][2], m[1][3] - Instance.m[1][3],
			m[2][0] - Instance.m[2][0], m[2][1] - Instance.m[2][1], m[2][2] - Instance.m[2][2], m[2][3] - Instance.m[2][3],
			m[3][0] - Instance.m[3][0], m[3][1] - Instance.m[3][1], m[3][2] - Instance.m[3][2], m[3][3] - Instance.m[3][3]
		);
	}


	/**
	 * @brief 두 행렬을 곱합니다.
	 *
	 * @param Instance 행렬의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬을 곱한 결과를 반환합니다.
	 */
	Matrix4x4<T> operator*(Matrix4x4<T>&& Instance)
	{
		return Matrix4x4(
			m[0][0] * Instance.m[0][0] + m[0][1] * Instance.m[1][0] + m[0][2] * Instance.m[2][0] + m[0][3] * Instance.m[3][0],
			m[0][0] * Instance.m[0][1] + m[0][1] * Instance.m[1][1] + m[0][2] * Instance.m[2][1] + m[0][3] * Instance.m[3][1],
			m[0][0] * Instance.m[0][2] + m[0][1] * Instance.m[1][2] + m[0][2] * Instance.m[2][2] + m[0][3] * Instance.m[3][2],
			m[0][0] * Instance.m[0][3] + m[0][1] * Instance.m[1][3] + m[0][2] * Instance.m[2][3] + m[0][3] * Instance.m[3][3],
			m[1][0] * Instance.m[0][0] + m[1][1] * Instance.m[1][0] + m[1][2] * Instance.m[2][0] + m[1][3] * Instance.m[3][0],
			m[1][0] * Instance.m[0][1] + m[1][1] * Instance.m[1][1] + m[1][2] * Instance.m[2][1] + m[1][3] * Instance.m[3][1],
			m[1][0] * Instance.m[0][2] + m[1][1] * Instance.m[1][2] + m[1][2] * Instance.m[2][2] + m[1][3] * Instance.m[3][2],
			m[1][0] * Instance.m[0][3] + m[1][1] * Instance.m[1][3] + m[1][2] * Instance.m[2][3] + m[1][3] * Instance.m[3][3],
			m[2][0] * Instance.m[0][0] + m[2][1] * Instance.m[1][0] + m[2][2] * Instance.m[2][0] + m[2][3] * Instance.m[3][0],
			m[2][0] * Instance.m[0][1] + m[2][1] * Instance.m[1][1] + m[2][2] * Instance.m[2][1] + m[2][3] * Instance.m[3][1],
			m[2][0] * Instance.m[0][2] + m[2][1] * Instance.m[1][2] + m[2][2] * Instance.m[2][2] + m[2][3] * Instance.m[3][2],
			m[2][0] * Instance.m[0][3] + m[2][1] * Instance.m[1][3] + m[2][2] * Instance.m[2][3] + m[2][3] * Instance.m[3][3],
			m[3][0] * Instance.m[0][0] + m[3][1] * Instance.m[1][0] + m[3][2] * Instance.m[2][0] + m[3][3] * Instance.m[3][0],
			m[3][0] * Instance.m[0][1] + m[3][1] * Instance.m[1][1] + m[3][2] * Instance.m[2][1] + m[3][3] * Instance.m[3][1],
			m[3][0] * Instance.m[0][2] + m[3][1] * Instance.m[1][2] + m[3][2] * Instance.m[2][2] + m[3][3] * Instance.m[3][2],
			m[3][0] * Instance.m[0][3] + m[3][1] * Instance.m[1][3] + m[3][2] * Instance.m[2][3] + m[3][3] * Instance.m[3][3],
		);
	}


	/**
	 * @brief 두 행렬을 곱합니다.
	 *
	 * @param Instance 행렬의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬을 곱한 결과를 반환합니다.
	 */
	Matrix4x4<T> operator*(const Matrix4x4<T>& Instance)
	{
		return Matrix4x4(
			m[0][0] * Instance.m[0][0] + m[0][1] * Instance.m[1][0] + m[0][2] * Instance.m[2][0] + m[0][3] * Instance.m[3][0],
			m[0][0] * Instance.m[0][1] + m[0][1] * Instance.m[1][1] + m[0][2] * Instance.m[2][1] + m[0][3] * Instance.m[3][1],
			m[0][0] * Instance.m[0][2] + m[0][1] * Instance.m[1][2] + m[0][2] * Instance.m[2][2] + m[0][3] * Instance.m[3][2],
			m[0][0] * Instance.m[0][3] + m[0][1] * Instance.m[1][3] + m[0][2] * Instance.m[2][3] + m[0][3] * Instance.m[3][3],
			m[1][0] * Instance.m[0][0] + m[1][1] * Instance.m[1][0] + m[1][2] * Instance.m[2][0] + m[1][3] * Instance.m[3][0],
			m[1][0] * Instance.m[0][1] + m[1][1] * Instance.m[1][1] + m[1][2] * Instance.m[2][1] + m[1][3] * Instance.m[3][1],
			m[1][0] * Instance.m[0][2] + m[1][1] * Instance.m[1][2] + m[1][2] * Instance.m[2][2] + m[1][3] * Instance.m[3][2],
			m[1][0] * Instance.m[0][3] + m[1][1] * Instance.m[1][3] + m[1][2] * Instance.m[2][3] + m[1][3] * Instance.m[3][3],
			m[2][0] * Instance.m[0][0] + m[2][1] * Instance.m[1][0] + m[2][2] * Instance.m[2][0] + m[2][3] * Instance.m[3][0],
			m[2][0] * Instance.m[0][1] + m[2][1] * Instance.m[1][1] + m[2][2] * Instance.m[2][1] + m[2][3] * Instance.m[3][1],
			m[2][0] * Instance.m[0][2] + m[2][1] * Instance.m[1][2] + m[2][2] * Instance.m[2][2] + m[2][3] * Instance.m[3][2],
			m[2][0] * Instance.m[0][3] + m[2][1] * Instance.m[1][3] + m[2][2] * Instance.m[2][3] + m[2][3] * Instance.m[3][3],
			m[3][0] * Instance.m[0][0] + m[3][1] * Instance.m[1][0] + m[3][2] * Instance.m[2][0] + m[3][3] * Instance.m[3][0],
			m[3][0] * Instance.m[0][1] + m[3][1] * Instance.m[1][1] + m[3][2] * Instance.m[2][1] + m[3][3] * Instance.m[3][1],
			m[3][0] * Instance.m[0][2] + m[3][1] * Instance.m[1][2] + m[3][2] * Instance.m[2][2] + m[3][3] * Instance.m[3][2],
			m[3][0] * Instance.m[0][3] + m[3][1] * Instance.m[1][3] + m[3][2] * Instance.m[2][3] + m[3][3] * Instance.m[3][3],
		);
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix4x4<T>& operator+=(Matrix4x4<T>&& Instance) noexcept
	{
		m[0][0] += Instance.m[0][0]; m[0][1] += Instance.m[0][1]; m[0][2] += Instance.m[0][2]; m[0][3] += Instance.m[0][3];
		m[1][0] += Instance.m[1][0]; m[1][1] += Instance.m[1][1]; m[1][2] += Instance.m[1][2]; m[1][3] += Instance.m[1][3];
		m[2][0] += Instance.m[2][0]; m[2][1] += Instance.m[2][1]; m[2][2] += Instance.m[2][2]; m[2][3] += Instance.m[2][3];
		m[3][0] += Instance.m[3][0]; m[3][1] += Instance.m[3][1]; m[3][2] += Instance.m[3][2]; m[3][3] += Instance.m[3][3];

		return *this;
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix4x4<T>& operator+=(const Matrix4x4<T>& Instance) noexcept
	{
		m[0][0] += Instance.m[0][0]; m[0][1] += Instance.m[0][1]; m[0][2] += Instance.m[0][2]; m[0][3] += Instance.m[0][3];
		m[1][0] += Instance.m[1][0]; m[1][1] += Instance.m[1][1]; m[1][2] += Instance.m[1][2]; m[1][3] += Instance.m[1][3];
		m[2][0] += Instance.m[2][0]; m[2][1] += Instance.m[2][1]; m[2][2] += Instance.m[2][2]; m[2][3] += Instance.m[2][3];
		m[3][0] += Instance.m[3][0]; m[3][1] += Instance.m[3][1]; m[3][2] += Instance.m[3][2]; m[3][3] += Instance.m[3][3];

		return *this;
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix4x4<T>& operator-=(Matrix4x4<T>&& Instance) noexcept
	{
		m[0][0] -= Instance.m[0][0]; m[0][1] -= Instance.m[0][1]; m[0][2] -= Instance.m[0][2]; m[0][3] -= Instance.m[0][3];
		m[1][0] -= Instance.m[1][0]; m[1][1] -= Instance.m[1][1]; m[1][2] -= Instance.m[1][2]; m[1][3] -= Instance.m[1][3];
		m[2][0] -= Instance.m[2][0]; m[2][1] -= Instance.m[2][1]; m[2][2] -= Instance.m[2][2]; m[2][3] -= Instance.m[2][3];
		m[3][0] -= Instance.m[3][0]; m[3][1] -= Instance.m[3][1]; m[3][2] -= Instance.m[3][2]; m[3][3] -= Instance.m[3][3];

		return *this;
	}


	/**
	 * @brief 두 행렬에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix4x4<T>& operator-=(const Matrix4x4<T>& Instance) noexcept
	{
		m[0][0] -= Instance.m[0][0]; m[0][1] -= Instance.m[0][1]; m[0][2] -= Instance.m[0][2]; m[0][3] -= Instance.m[0][3];
		m[1][0] -= Instance.m[1][0]; m[1][1] -= Instance.m[1][1]; m[1][2] -= Instance.m[1][2]; m[1][3] -= Instance.m[1][3];
		m[2][0] -= Instance.m[2][0]; m[2][1] -= Instance.m[2][1]; m[2][2] -= Instance.m[2][2]; m[2][3] -= Instance.m[2][3];
		m[3][0] -= Instance.m[3][0]; m[3][1] -= Instance.m[3][1]; m[3][2] -= Instance.m[3][2]; m[3][3] -= Instance.m[3][3];

		return *this;
	}


	/**
	 * @brief 두 행렬의 원소가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 행렬입니다.
	 *
	 * @return 두 행렬의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(Matrix4x4<T>&& Instance) noexcept
	{
		return (m[0][0] == Instance.m[0][0])
			&& (m[0][1] == Instance.m[0][1])
			&& (m[0][2] == Instance.m[0][2])
			&& (m[0][3] == Instance.m[0][3])
			&& (m[1][0] == Instance.m[1][0])
			&& (m[1][1] == Instance.m[1][1])
			&& (m[1][2] == Instance.m[1][2])
			&& (m[1][3] == Instance.m[1][3])
			&& (m[2][0] == Instance.m[2][0])
			&& (m[2][1] == Instance.m[2][1])
			&& (m[2][2] == Instance.m[2][2])
			&& (m[2][3] == Instance.m[2][3])
			&& (m[3][0] == Instance.m[3][0])
			&& (m[3][1] == Instance.m[3][1])
			&& (m[3][2] == Instance.m[3][2])
			&& (m[3][3] == Instance.m[3][3]);
	}


	/**
	 * @brief 두 행렬의 원소가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 행렬입니다.
	 *
	 * @return 두 행렬의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(const Matrix4x4<T>& Instance) noexcept
	{
		return (m[0][0] == Instance.m[0][0])
			&& (m[0][1] == Instance.m[0][1])
			&& (m[0][2] == Instance.m[0][2])
			&& (m[0][3] == Instance.m[0][3])
			&& (m[1][0] == Instance.m[1][0])
			&& (m[1][1] == Instance.m[1][1])
			&& (m[1][2] == Instance.m[1][2])
			&& (m[1][3] == Instance.m[1][3])
			&& (m[2][0] == Instance.m[2][0])
			&& (m[2][1] == Instance.m[2][1])
			&& (m[2][2] == Instance.m[2][2])
			&& (m[2][3] == Instance.m[2][3])
			&& (m[3][0] == Instance.m[3][0])
			&& (m[3][1] == Instance.m[3][1])
			&& (m[3][2] == Instance.m[3][2])
			&& (m[3][3] == Instance.m[3][3]);
	}


	/**
	 * @brief 두 행렬의 원소가 일치하지 않는지 확인합니다.
	 *
	 * @param 일치하지 않는지 확인할 피 연산자입니다.
	 *
	 * @return 두 행렬의 원소가 일치하지 않으면 true, 일치하면 false를 반환합니다.
	 */
	bool operator!=(Matrix4x4<T>&& Instance) noexcept
	{
		return (m[0][0] != Instance.m[0][0])
			|| (m[0][1] != Instance.m[0][1])
			|| (m[0][2] != Instance.m[0][2])
			|| (m[0][3] != Instance.m[0][3])
			|| (m[1][0] != Instance.m[1][0])
			|| (m[1][1] != Instance.m[1][1])
			|| (m[1][2] != Instance.m[1][2])
			|| (m[1][3] != Instance.m[1][3])
			|| (m[2][0] != Instance.m[2][0])
			|| (m[2][1] != Instance.m[2][1])
			|| (m[2][2] != Instance.m[2][2])
			|| (m[2][3] != Instance.m[2][3])
			|| (m[3][0] != Instance.m[3][0])
			|| (m[3][1] != Instance.m[3][1])
			|| (m[3][2] != Instance.m[3][2])
			|| (m[3][3] != Instance.m[3][3]);
	}


	/**
	 * @brief 두 행렬의 원소가 일치하지 않는지 확인합니다.
	 *
	 * @param 일치하지 않는지 확인할 피 연산자입니다.
	 *
	 * @return 두 행렬의 원소가 일치하지 않으면 true, 일치하면 false를 반환합니다.
	 */
	bool operator!=(const Matrix4x4<T>& Instance) noexcept
	{
		return (m[0][0] != Instance.m[0][0])
			|| (m[0][1] != Instance.m[0][1])
			|| (m[0][2] != Instance.m[0][2])
			|| (m[0][3] != Instance.m[0][3])
			|| (m[1][0] != Instance.m[1][0])
			|| (m[1][1] != Instance.m[1][1])
			|| (m[1][2] != Instance.m[1][2])
			|| (m[1][3] != Instance.m[1][3])
			|| (m[2][0] != Instance.m[2][0])
			|| (m[2][1] != Instance.m[2][1])
			|| (m[2][2] != Instance.m[2][2])
			|| (m[2][3] != Instance.m[2][3])
			|| (m[3][0] != Instance.m[3][0])
			|| (m[3][1] != Instance.m[3][1])
			|| (m[3][2] != Instance.m[3][2])
			|| (m[3][3] != Instance.m[3][3]);
	}


	/**
	 * @brief 행렬을 단위 행렬로 설정합니다.
	 */
	void Identify()
	{
		m[0][0] = static_cast<T>(1); m[0][1] = static_cast<T>(0); m[0][2] = static_cast<T>(0); m[0][3] = static_cast<T>(0);
		m[1][0] = static_cast<T>(0); m[1][1] = static_cast<T>(1); m[1][2] = static_cast<T>(0); m[1][3] = static_cast<T>(0);
		m[2][0] = static_cast<T>(0); m[2][1] = static_cast<T>(0); m[2][2] = static_cast<T>(1); m[2][3] = static_cast<T>(0);
		m[3][0] = static_cast<T>(0); m[3][1] = static_cast<T>(0); m[3][2] = static_cast<T>(0); m[3][3] = static_cast<T>(1);
	}


	/**
	 * @brief 행렬의 원소입니다.
	 */
	T m[4][4];
};


/**
 * @brief int 타입의 2x2 행렬입니다.
 */
using Matrix2x2I = Matrix2x2<int32_t>;


/**
 * @brief float 타입의 2x2 행렬입니다.
 */
using Matrix2x2F = Matrix2x2<float>;


/**
 * @brief int 타입의 3x3 행렬입니다.
 */
using Matrix3x3I = Matrix3x3<int32_t>;


/**
 * @brief float 타입의 3x3 행렬입니다.
 */
using Matrix3x3F = Matrix3x3<float>;


/**
 * @brief int 타입의 4x4 행렬입니다.
 */
using Matrix4x4I = Matrix4x4<int32_t>;


/**
 * @brief float 타입의 4x4 행렬입니다.
 */
using Matrix4x4F = Matrix4x4<float>;