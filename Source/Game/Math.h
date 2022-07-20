#pragma once

// @third party code
#include <glm/glm.hpp>
// @third party code

#include <cstdint>
#include <chrono>
#include <random>


namespace Game
{
	/**
	 * 수학 관련 유틸리티 클래스입니다.
	 * @note 이 클래스는 해더만 추가한다면 인스턴스 생성 없이 바로 사용할 수 있습니다.
	 */
	class Math
	{
	public:
		/**
		 * 임의의 정수를 생성합니다.
		 * 
		 * @param InMinValue - 생성할 난수 범위의 최솟값입니다.
		 * @param InMaxValue - 생성할 난수 범위의 최댓값입니다.
		 * 
		 * @return - 생성된 정수를 반환합니다.
		 */
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


		/**
		 * 임의의 실수를 생성합니다.
		 * 
		 * @param InMinValue - 생성할 난수 범위의 최솟값입니다.
		 * @param InMaxValue - 생성할 난수 범위의 최댓값입니다.
		 * 
		 * @return - 생성된 난수를 반환합니다.
		 */
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


		/**
		 * 값을 특정 범위로 자릅니다.
		 * 
		 * @param InValue - 범위 내로 자르고자 하는 값입니다.
		 * @param InMinValue - 범위의 최솟값입니다.
		 * @param InMaxValue - 범위의 최댓값입니다.
		 * 
		 * @return - 범위 내의 값으로 자른 값을 반환합니다.
		 */
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


		/**
		 * 두 값을 선형 보간합니다.
		 * 
		 * @param InFirst - 보간을 수행할 두 값의 시작점입니다.
		 * @param InLast - 보간을 수행할 두 값의 끝점입니다.
		 * @param InAlpha - 두 값의 보간 비율입니다. 이때, 범위는 0 ~ 1입니다.
		 * 
		 * @return - 입력받은 두 값의 선형 보간값을 반환합니다.
		 */
		template<typename T>
		inline static T Lerp(const T& InFirst, const T& InLast, float InAlpha)
		{
			InAlpha = Clamp<float>(InAlpha, 0.0f, 1.0f);
			return (InFirst * (1.0f - InAlpha)) + (InLast * InAlpha);
		}
	};


	/**
	 * 선형 색상을 정의합니다.
	 */
	using LinearColor = glm::vec4;


	/**
	 * 색상을 관리하는 클래스입니다.
	 * @note 이 클래스는 해더만 추가한다면 인스턴스 생성 없이 바로 사용할 수 있습니다.
	 */
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
	};
}