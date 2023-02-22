#include "AudioPlayComponent.h"
#include "ContentManager.h"
#include "Sound.h"

AudioPlayComponent::AudioPlayComponent(GameObject* Object, const std::string& AudioSignature)
	: AudioComponent(Object)
	, AudioSignature_(AudioSignature) {}

void AudioPlayComponent::Tick()
{
}

void AudioPlayComponent::SetVolume(float Volume)
{
	ContentManager::Get().GetSound(AudioSignature_).SetVolume(Volume);
}

float AudioPlayComponent::GetVolume()
{
	return ContentManager::Get().GetSound(AudioSignature_).GetVolume();
}

void AudioPlayComponent::SetLooping(bool bIsLoop)
{
	ContentManager::Get().GetSound(AudioSignature_).SetLooping(bIsLoop);
}

bool AudioPlayComponent::GetLooping()
{
	return ContentManager::Get().GetSound(AudioSignature_).GetLooping();
}

void AudioPlayComponent::Play()
{
	ContentManager::Get().GetSound(AudioSignature_).Play();
}

bool AudioPlayComponent::IsPlaying()
{
	return ContentManager::Get().GetSound(AudioSignature_).IsPlaying();
}

bool AudioPlayComponent::IsDone()
{
	return ContentManager::Get().GetSound(AudioSignature_).IsDone();
}

void AudioPlayComponent::Stop()
{
	ContentManager::Get().GetSound(AudioSignature_).Stop();
}

bool AudioPlayComponent::IsStopping()
{
	return ContentManager::Get().GetSound(AudioSignature_).IsStopping();
}

void AudioPlayComponent::Reset()
{
	ContentManager::Get().GetSound(AudioSignature_).Reset();
}
