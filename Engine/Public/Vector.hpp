#pragma once

#include <cmath>
#include <cstdint>
#include <algorithm>


/**
 * @brief 템플릿 기반의 2차원 벡터입니다.
 */
template <typename T>
struct Vector2
{
	/**
	 * @brief 벡터의 기본 생성자입니다.
	 * 
	 * @note 모든 원소의 값을 0으로 초기화합니다.
	 */
	Vector2() noexcept
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
	}


	/**
	 * @brief 벡터의 생성자입니다.
	 *
	 * @param xx 벡터의 x 성분입니다.
	 * @param yy 벡터의 y 성분입니다.
	 */
	Vector2(T&& xx, T&& yy)
	{
		x = xx;
		y = yy;
	}


	/**
	 * @brief 벡터의 생성자입니다.
	 *
	 * @param xx 벡터의 x 성분입니다.
	 * @param yy 벡터의 y 성분입니다.
	 */
	Vector2(const T& xx, const T& yy)
	{
		x = xx;
		y = yy;
	}


	/**
	 * @brief 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Vector2(T&& Element) noexcept
	{
		x = Element;
		y = Element;
	}


	/**
	 * @brief 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Vector2(const T& Element) noexcept
	{
		x = Element;
		y = Element;
	}


	/**
	 * @brief 벡터의 복사 생성자입니다.
	 *
	 * @param Instance 원소를 복사할 벡터의 인스턴스입니다.
	 */
	Vector2(const Vector2<T>& Instance) noexcept
	{
		x = Instance.x;
		y = Instance.y;
	}


	/**
	 * @brief 벡터의 복사 생성자입니다.
	 *
	 * @param Instance 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 */
	Vector2(Vector2<T>&& Instance) noexcept
	{
		x = Instance.x;
		y = Instance.y;
	}


	/**
	 * @brief 벡터의 대입 연산자 입니다.
	 *
	 * @param Instance 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator=(const Vector2<T>& Instance) noexcept
	{
		if (this == &Instance) return *this;

		x = Instance.x;
		y = Instance.y;

		return *this;
	}


	/**
	 * @brief 벡터의 대입 연산자 입니다.
	 *
	 * @param Instance 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator=(Vector2<T>&& Instance) noexcept
	{
		if (this == &Instance) return *this;

		x = Instance.x;
		y = Instance.y;

		return *this;
	}


	/**
	 * @brief 벡터의 원소에 -부호를 취합니다.
	 *
	 * @return 벡터의 원소에 -부호를 취한 새로운 벡터를 반환합니다.
	 */
	Vector2<T> operator-() const
	{
		return Vector2<T>(-x, -y);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector2<T> operator+(const Vector2<T>& Instance) const
	{
		return Vector2<T>(x + Instance.x, y + Instance.y);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector2<T> operator+(Vector2<T>&& Instance) const
	{
		return Vector2<T>(x + Instance.x, y + Instance.y);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector2<T> operator-(const Vector2<T>& Instance) const
	{
		return Vector2<T>(x - Instance.x, y - Instance.y);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector2<T> operator-(Vector2<T>&& Instance) const
	{
		return Vector2<T>(x - Instance.x, y - Instance.y);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param Instance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector2<T> operator*(const Vector2<T>& Instance) const
	{
		return Vector2<T>(x * Instance.x, y * Instance.y);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param Instance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector2<T> operator*(Vector2<T>&& Instance) const
	{
		return Vector2<T>(x * Instance.x, y * Instance.y);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator+=(const Vector2<T>& Instance) noexcept
	{
		x += Instance.x;
		y += Instance.y;

		return *this;
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator+=(Vector2<T>&& Instance) noexcept
	{
		x += Instance.x;
		y += Instance.y;

		return *this;
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator-=(const Vector2<T>& Instance) noexcept
	{
		x -= Instance.x;
		y -= Instance.y;

		return *this;
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector2<T>& operator-=(Vector2<T>&& Instance) noexcept
	{
		x -= Instance.x;
		y -= Instance.y;

		return *this;
	}


	/**
	 * @brief 두 벡터가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(const Vector2<T>& Instance) noexcept
	{
		return (x == Instance.x) && (y == Instance.y);
	}


	/**
	 * @brief 두 벡터가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(Vector2<T>&& Instance) noexcept
	{
		return (x == Instance.x) && (y == Instance.y);
	}


	/**
	 * @brief 두 벡터가 일치하지 않는지 확인합니다.
	 *
	 * @param Instance 일치하지 않는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소 중 하나라도 일치하지 않으면 true, 모두 일치하면 false를 반환합니다.
	 */
	bool operator!=(const Vector2<T>& Instance) noexcept
	{
		return (x != Instance.x) || (y != Instance.y);
	}


	/**
	 * @brief 두 벡터가 일치하지 않는지 확인합니다.
	 *
	 * @param Instance 일치하지 않는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소 중 하나라도 일치하지 않으면 true, 모두 일치하면 false를 반환합니다.
	 */
	bool operator!=(Vector2<T>&& Instance) noexcept
	{
		return (x != Instance.x) || (y != Instance.y);
	}


	/**
	 * @brief 벡터의 첫 번째 원소입니다.
	 */
	T x;


	/**
	 * @brief 벡터의 두 번째 원소입니다.
	 */
	T y;
};


/**
 * @brief 템플릿 기반의 3차원 벡터입니다.
 */
template <typename T>
struct Vector3
{
	/**
	 * @brief 벡터의 기본 생성자입니다.
	 * 
	 * @note 모든 원소의 값을 0으로 초기화합니다.
	 */
	Vector3() noexcept
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
		z = static_cast<T>(0);
	}


	/**
	 * @brief 벡터의 생성자입니다.
	 *
	 * @param xx 벡터의 x 성분입니다.
	 * @param yy 벡터의 y 성분입니다.
	 * @param zz 벡터의 z 성분입니다.
	 */
	Vector3(T&& xx, T&& yy, T&& zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}


	/**
	 * @brief 벡터의 생성자입니다.
	 *
	 * @param xx 벡터의 x 성분입니다.
	 * @param yy 벡터의 y 성분입니다.
	 * @param zz 벡터의 z 성분입니다.
	 */
	Vector3(const T& xx, const T& yy, const T& zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}


	/**
	 * @brief 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Vector3(T&& Element) noexcept
	{
		x = Element;
		y = Element;
		z = Element;
	}


	/**
	 * @brief 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Vector3(const T& Element) noexcept
	{
		x = Element;
		y = Element;
		z = Element;
	}


	/**
	 * @brief 벡터의 복사 생성자입니다.
	 *
	 * @param Instance 원소를 복사할 벡터의 인스턴스입니다.
	 */
	Vector3(const Vector3<T>& Instance) noexcept
	{
		x = Instance.x;
		y = Instance.y;
		z = Instance.z;
	}


	/**
	 * @brief 벡터의 복사 생성자입니다.
	 *
	 * @param Instance 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 */
	Vector3(Vector3<T>&& Instance) noexcept
	{
		x = Instance.x;
		y = Instance.y;
		z = Instance.z;
	}


	/**
	 * @brief 벡터의 대입 연산자 입니다.
	 *
	 * @param Instance 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator=(const Vector3<T>& Instance) noexcept
	{
		if (this == &Instance) return *this;

		x = Instance.x;
		y = Instance.y;
		z = Instance.z;

		return *this;
	}


	/**
	 * @brief 벡터의 대입 연산자 입니다.
	 *
	 * @param Instance 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator=(Vector3<T>&& Instance) noexcept
	{
		if (this == &Instance) return *this;

		x = Instance.x;
		y = Instance.y;
		z = Instance.z;

		return *this;
	}


	/**
	 * @brief 벡터의 원소에 -부호를 취합니다.
	 *
	 * @return 벡터의 원소에 -부호를 취한 새로운 벡터를 반환합니다.
	 */
	Vector3<T> operator-() const
	{
		return Vector3<T>(-x, -y, -z);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector3<T> operator+(const Vector3<T>& Instance) const
	{
		return Vector3<T>(x + Instance.x, y + Instance.y, z + Instance.z);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector3<T> operator+(Vector3<T>&& Instance) const
	{
		return Vector3<T>(x + Instance.x, y + Instance.y, z + Instance.z);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector3<T> operator-(const Vector3<T>& Instance) const
	{
		return Vector3<T>(x - Instance.x, y - Instance.y, z - Instance.z);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector3<T> operator-(Vector3<T>&& Instance) const
	{
		return Vector3<T>(x - Instance.x, y - Instance.y, z - Instance.z);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param Instance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector3<T> operator*(const Vector3<T>& Instance) const
	{
		return Vector3<T>(x * Instance.x, y * Instance.y, z * Instance.z);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param Instance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector3<T> operator*(Vector3<T>&& Instance) const
	{
		return Vector3<T>(x * Instance.x, y * Instance.y, z * Instance.z);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator+=(const Vector3<T>& Instance) noexcept
	{
		x += Instance.x;
		y += Instance.y;
		z += Instance.z;

		return *this;
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator+=(Vector3<T>&& Instance) noexcept
	{
		x += Instance.x;
		y += Instance.y;
		z += Instance.z;

		return *this;
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator-=(const Vector3<T>& Instance) noexcept
	{
		x -= Instance.x;
		y -= Instance.y;
		z -= Instance.z;

		return *this;
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector3<T>& operator-=(Vector3<T>&& Instance) noexcept
	{
		x -= Instance.x;
		y -= Instance.y;
		z -= Instance.z;

		return *this;
	}


	/**
	 * @brief 두 벡터가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(const Vector3<T>& Instance) noexcept
	{
		return (x == Instance.x) && (y == Instance.y) && (z == Instance.z);
	}


	/**
	 * @brief 두 벡터가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(Vector3<T>&& Instance) noexcept
	{
		return (x == Instance.x) && (y == Instance.y) && (z == Instance.z);
	}


	/**
	 * @brief 두 벡터가 일치하지 않는지 확인합니다.
	 *
	 * @param Instance 일치하지 않는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소 중 하나라도 일치하지 않으면 true, 모두 일치하면 false를 반환합니다.
	 */
	bool operator!=(const Vector3<T>& Instance) noexcept
	{
		return (x != Instance.x) || (y != Instance.y) || (z != Instance.z);
	}


	/**
	 * @brief 두 벡터가 일치하지 않는지 확인합니다.
	 *
	 * @param Instance 일치하지 않는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소 중 하나라도 일치하지 않으면 true, 모두 일치하면 false를 반환합니다.
	 */
	bool operator!=(Vector3<T>&& Instance) noexcept
	{
		return (x != Instance.x) || (y != Instance.y) || (z != Instance.z);
	}


	/**
	 * @brief 벡터의 첫 번째 원소입니다.
	 */
	T x;


	/**
	 * @brief 벡터의 두 번째 원소입니다.
	 */
	T y;


	/**
	 * @brief 벡터의 세 번째 원소입니다.
	 */
	T z;
};



/**
 * @brief 템플릿 기반의 4차원 벡터입니다.
 */
template <typename T>
struct Vector4
{
	/**
	 * @brief 벡터의 기본 생성자입니다.
	 * 
	 * @note 모든 원소의 값을 0으로 초기화합니다.
	 */
	Vector4() noexcept
	{
		x = static_cast<T>(0);
		y = static_cast<T>(0);
		z = static_cast<T>(0);
		w = static_cast<T>(0);
	}


	/**
	 * @brief 벡터의 생성자입니다.
	 *
	 * @param xx 벡터의 x 성분입니다.
	 * @param yy 벡터의 y 성분입니다.
	 * @param zz 벡터의 z 성분입니다.
	 * @param ww 벡터의 w 성분입니다.
	 */
	Vector4(T&& xx, T&& yy, T&& zz, T&& ww)
	{
		x = xx;
		y = yy;
		z = zz;
		w = ww;
	}


	/**
	 * @brief 벡터의 생성자입니다.
	 *
	 * @param xx 벡터의 x 성분입니다.
	 * @param yy 벡터의 y 성분입니다.
	 * @param zz 벡터의 z 성분입니다.
	 * @param ww 벡터의 w 성분입니다.
	 */
	Vector4(const T& xx, const T& yy, const T& zz, const T& ww)
	{
		x = xx;
		y = yy;
		z = zz;
		w = ww;
	}


	/**
	 * @brief 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Vector4(T&& Element) noexcept
	{
		x = Element;
		y = Element;
		z = Element;
		w = Element;
	}


	/**
	 * @brief 벡터의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param Element 모든 원소를 초기화 할 값입니다.
	 */
	Vector4(const T& Element) noexcept
	{
		x = Element;
		y = Element;
		z = Element;
		w = Element;
	}


	/**
	 * @brief 벡터의 복사 생성자입니다.
	 *
	 * @param Instance 원소를 복사할 벡터의 인스턴스입니다.
	 */
	Vector4(const Vector4<T>& Instance) noexcept
	{
		x = Instance.x;
		y = Instance.y;
		z = Instance.z;
		w = Instance.w;
	}


	/**
	 * @brief 벡터의 복사 생성자입니다.
	 *
	 * @param Instance 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 */
	Vector4(Vector4<T>&& Instance) noexcept
	{
		x = Instance.x;
		y = Instance.y;
		z = Instance.z;
		w = Instance.w;
	}


	/**
	 * @brief 벡터의 대입 연산자 입니다.
	 *
	 * @param Instance 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator=(const Vector4<T>& Instance) noexcept
	{
		if (this == &Instance) return *this;

		x = Instance.x;
		y = Instance.y;
		z = Instance.z;
		w = Instance.w;

		return *this;
	}


	/**
	 * @brief 벡터의 대입 연산자 입니다.
	 *
	 * @param Instance 원소를 복사할 벡터 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator=(Vector4<T>&& Instance) noexcept
	{
		if (this == &Instance) return *this;

		x = Instance.x;
		y = Instance.y;
		z = Instance.z;
		w = Instance.w;

		return *this;
	}


	/**
	 * @brief 벡터의 원소에 -부호를 취합니다.
	 *
	 * @return 벡터의 원소에 -부호를 취한 새로운 벡터를 반환합니다.
	 */
	Vector4<T> operator-() const
	{
		return Vector4<T>(-x, -y, -z, -w);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector4<T> operator+(const Vector4<T>& Instance) const
	{
		return Vector4<T>(x + Instance.x, y + Instance.y, z + Instance.z, w + Instance.w);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 벡터의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Vector4<T> operator+(Vector4<T>&& Instance) const
	{
		return Vector4<T>(x + Instance.x, y + Instance.y, z + Instance.z, w + Instance.w);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector4<T> operator-(const Vector4<T>& Instance) const
	{
		return Vector4<T>(x - Instance.x, y - Instance.y, z - Instance.z, w - Instance.w);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 벡터의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Vector4<T> operator-(Vector4<T>&& Instance) const
	{
		return Vector4<T>(x - Instance.x, y - Instance.y, z - Instance.z, w - Instance.w);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param Instance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector4<T> operator*(const Vector4<T>& Instance) const
	{
		return Vector4<T>(x * Instance.x, y * Instance.y, z * Instance.z, w * Instance.w);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 각각 곱합니다.
	 *
	 * @param Instance 벡터의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 벡터에 대응하는 원소를 곱한 결과를 반환합니다.
	 */
	Vector4<T> operator*(Vector4<T>&& Instance) const
	{
		return Vector4<T>(x * Instance.x, y * Instance.y, z * Instance.z, w * Instance.w);
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator+=(const Vector4<T>& Instance) noexcept
	{
		x += Instance.x;
		y += Instance.y;
		z += Instance.z;
		w += Instance.w;

		return *this;
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 더합니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator+=(Vector4<T>&& Instance) noexcept
	{
		x += Instance.x;
		y += Instance.y;
		z += Instance.z;
		w += Instance.w;

		return *this;
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator-=(const Vector4<T>& Instance) noexcept
	{
		x -= Instance.x;
		y -= Instance.y;
		z -= Instance.z;
		w -= Instance.w;

		return *this;
	}


	/**
	 * @brief 두 벡터에 대응하는 원소를 뺍니다.
	 *
	 * @param Instance 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 벡터의 참조자를 반환합니다.
	 */
	Vector4<T>& operator-=(Vector4<T>&& Instance) noexcept
	{
		x -= Instance.x;
		y -= Instance.y;
		z -= Instance.z;
		w -= Instance.w;

		return *this;
	}


	/**
	 * @brief 두 벡터가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(const Vector4<T>& Instance) noexcept
	{
		return (x == Instance.x) && (y == Instance.y) && (z == Instance.z) && (w == Instance.w);
	}


	/**
	 * @brief 두 벡터가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소가 모두 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(Vector4<T>&& Instance) noexcept
	{
		return (x == Instance.x) && (y == Instance.y) && (z == Instance.z) && (w == Instance.w);
	}


	/**
	 * @brief 두 벡터가 일치하지 않는지 확인합니다.
	 *
	 * @param Instance 일치하지 않는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소 중 하나라도 일치하지 않으면 true, 모두 일치하면 false를 반환합니다.
	 */
	bool operator!=(const Vector4<T>& Instance) noexcept
	{
		return (x != Instance.x) || (y != Instance.y) || (z != Instance.z) || (w != Instance.w);
	}


	/**
	 * @brief 두 벡터가 일치하지 않는지 확인합니다.
	 *
	 * @param Instance 일치하지 않는지 확인할 피연산자입니다.
	 *
	 * @return 두 벡터의 원소 중 하나라도 일치하지 않으면 true, 모두 일치하면 false를 반환합니다.
	 */
	bool operator!=(Vector4<T>&& Instance) noexcept
	{
		return (x != Instance.x) || (y != Instance.y) || (z != Instance.z) || (w != Instance.w);
	}


	/**
	 * @brief 벡터의 첫 번째 원소입니다.
	 */
	T x;


	/**
	 * @brief 벡터의 두 번째 원소입니다.
	 */
	T y;


	/**
	 * @brief 벡터의 세 번째 원소입니다.
	 */
	T z;


	/**
	 * @brief 벡터의 네 번째 원소입니다.
	 */
	T w;
};


/**
 * @brief int 타입의 2차원 벡터입니다.
 */
using Vec2i = Vector2<int32_t>;


/**
 * @brief float 타입의 2차원 벡터입니다.
 */
using Vec2f = Vector2<float>;


/**
 * @brief int 타입의 3차원 벡터입니다.
 */
using Vec3i = Vector3<int32_t>;


/**
 * @brief float 타입의 3차원 벡터입니다.
 */
using Vec3f = Vector3<float>;


/**
 * @brief int 타입의 4차원 벡터입니다.
 */
using Vec4i = Vector4<int32_t>;


/**
 * @brief float 타입의 4차원 벡터입니다.
 */
using Vec4f = Vector4<float>;