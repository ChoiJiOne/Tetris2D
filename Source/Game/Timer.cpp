// @third party code - BEGIN SDL2
#include <glfw/glfw3.h>
// @third party code - END

#include "Timer.h"

namespace Game
{
	Timer::~Timer()
	{
	}

	float Timer::DeltaTime() const
	{
		if (bIsStop)
		{
			return 0.0f;
		}
		else
		{
			return CurrentTime - PreviousTime;
		}
	}

	float Timer::TotalTime() const
	{
		if (bIsStop)
		{
			return StopTime - PausedTime - BaseTime;
		}
		else
		{
			return CurrentTime - PausedTime - BaseTime;
		}
	}

	void Timer::Reset()
	{
		float TickTime = static_cast<float>(glfwGetTime());

		BaseTime = TickTime;
		PausedTime = 0.0f;
		StopTime = 0.0f;
		PreviousTime = TickTime;
		CurrentTime = TickTime;
	}

	void Timer::Start()
	{
		if (bIsStop)
		{
			float TickTime = static_cast<float>(glfwGetTime());

			PausedTime += (TickTime - StopTime);
			PreviousTime = TickTime;
			StopTime = 0.0f;

			bIsStop = false;
		}
	}

	void Timer::Stop()
	{
		if (!bIsStop)
		{
			float TickTime = static_cast<float>(glfwGetTime());

			StopTime = TickTime;

			bIsStop = true;
		}
	}

	void Timer::Tick()
	{
		PreviousTime = CurrentTime;
		CurrentTime = static_cast<float>(glfwGetTime());
	}
}