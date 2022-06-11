#include "../Public/GameTimer.h"


GameTimer::~GameTimer()
{
}

float GameTimer::DeltaTime() const
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

float GameTimer::TotalTime() const
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

void GameTimer::Reset()
{
	uint64_t TickTime = SDL_GetTicks64();

	BaseTime = TickTime;
	PausedTime = 0ULL;
	StopTime = 0ULL;
	PreviousTime = TickTime;
	CurrentTime = TickTime;
}

void GameTimer::Start()
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

void GameTimer::Stop()
{
	if (!bIsStop)
	{
		uint64_t TickTime = SDL_GetTicks64();

		StopTime = TickTime;

		bIsStop = true;
	}
}

void GameTimer::Tick()
{
	PreviousTime = CurrentTime;
	CurrentTime = SDL_GetTicks64();
}