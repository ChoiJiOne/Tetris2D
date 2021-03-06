#pragma once

#include <cstdint>


namespace Game
{
	/**
	 * 게임 타이머 클래스입니다.
	 */
	class Timer
	{
	public:
		/**
		 * 타이머 클래스의 생성자입니다.
		 *
		 * @note 생성자에서 초기화를 수행하지 않으므로 반드시 Start 혹은 Reset 메서드를 호출해야 합니다.
		 */
		Timer() = default;


		/**
		 * 타이머 클래스의 가상 소멸자입니다.
		 */
		virtual ~Timer();


		/**
		 * 타이머의 델타 시간값을 반환합니다.
		 *
		 * @return 밀리초 단위의 델타 시간값을 반환합니다.
		 */
		float DeltaTime() const;


		/**
		 * 타이머가 중지된 시간을 제외한 전체 시간값을 반환합니다.
		 *
		 * @return 타이머가 시작된 이후의 중지된 시간을 제외한 전체 시간값을 밀리초 단위로 반환합니다.
		 */
		float TotalTime() const;


		/**
		 * 타이머의 모든 상태를 리셋합니다.
		 */
		void Reset();


		/**
		 * 타이머를 활성화시킵니다.
		 */
		void Start();


		/**
		 * 타이머를 중지시킵니다.
		 */
		void Stop();


		/**
		 * 타이머를 업데이트합니다.
		 */
		void Tick();


	private:
		/**
		 * 타이머의 중지 여부를 확인합니다.
		 */
		bool bIsStop = false;


		/**
		 * 타이머가 시작된 시간을 나타냅니다.
		 */
		float BaseTime = 0.0f;


		/**
		 * 타이머가 중지된 동안의 누적 시간을 나타냅니다.
		 */
		float PausedTime = 0.0f;


		/**
		 * 타이머가 중지된 시간을 나타냅니다.
		 */
		float StopTime = 0.0f;


		/**
		 * 직전의 Tick 호출 시간을 나타냅니다.
		 */
		float PreviousTime = 0.0f;


		/**
		 * Tick 호출 시간을 나타냅니다.
		 */
		float CurrentTime = 0.0f;
	};
}