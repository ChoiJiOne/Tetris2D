// @third party code - BEGIN SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
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
			return static_cast<float>(CurrentTime - PreviousTime) / 1000.0f;
		}
	}

	float Timer::TotalTime() const
	{
		if (bIsStop)
		{
			return static_cast<float>(StopTime - PausedTime - BaseTime) / 1000.0f;
		}
		else
		{
			return static_cast<float>(CurrentTime - PausedTime - BaseTime) / 1000.0f;
		}
	}

	void Timer::Reset()
	{
		uint64_t TickTime = SDL_GetTicks64();

		BaseTime = TickTime;
		PausedTime = 0ULL;
		StopTime = 0ULL;
		PreviousTime = TickTime;
		CurrentTime = TickTime;
	}

	void Timer::Start()
	{
		if (bIsStop)
		{
			uint64_t TickTime = SDL_GetTicks64();

			PausedTime += (TickTime - StopTime);
			PreviousTime = TickTime;
			StopTime = 0ULL;

			bIsStop = false;
		}
	}

	void Timer::Stop()
	{
		if (!bIsStop)
		{
			uint64_t TickTime = SDL_GetTicks64();

			StopTime = TickTime;

			bIsStop = true;
		}
	}

	void Timer::Tick()
	{
		PreviousTime = CurrentTime;
		CurrentTime = SDL_GetTicks64();
	}
}