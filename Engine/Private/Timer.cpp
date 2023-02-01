#include "Timer.h"
#include "Macro.h"

#include <windows.h>

Timer::Timer()
{
	int64_t CounterPerSeconds;
	CHECK((QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&CounterPerSeconds))), "failed to query performance frequency");

	SecondsPerCounter_ = 1.0 / static_cast<double>(CounterPerSeconds);
}

float Timer::GetDeltaTime() const
{
	float DeltaTime = 0.0f;

	if (!bIsStop_)
	{
		DeltaTime = static_cast<float>(CurrTime_ - PrevTime_) * static_cast<float>(SecondsPerCounter_);
	}

	return DeltaTime;
}

float Timer::GetTotalTime() const
{
	float TotalTime = static_cast<float>(SecondsPerCounter_);

	if (bIsStop_)
	{
		TotalTime *= static_cast<float>(StopTime_ - PausedTime_ - BaseTime_);
	}
	else
	{
		TotalTime *= static_cast<float>(CurrTime_ - PausedTime_ - BaseTime_);
	}

	return TotalTime;
}

void Timer::Reset()
{
	int64_t Counter = GetTickCounter();

	bIsStop_ = false;
	BaseTime_ = Counter;
	PausedTime_ = 0LL;
	StopTime_ = 0LL;
	PrevTime_ = Counter;
	CurrTime_ = Counter;
}

void Timer::Start()
{
	if (bIsStop_)
	{
		int64_t Counter = GetTickCounter();

		PausedTime_ += (Counter - StopTime_);
		PrevTime_ = Counter;
		StopTime_ = 0LL;
		bIsStop_ = false;
	}
}

void Timer::Stop()
{
	if (!bIsStop_)
	{
		StopTime_ = GetTickCounter();
		bIsStop_ = true;
	}
}

void Timer::Tick()
{
	PrevTime_ = CurrTime_;
	CurrTime_ = GetTickCounter();
}

int64_t Timer::GetTickCounter()
{
	int64_t Counter = 0LL;
	CHECK((QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&Counter))), "failed to query performance counter");

	return Counter;
}