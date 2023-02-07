#include "BackgroundAudioComponent.h"
#include "Background.h"

BackgroundAudioComponent::BackgroundAudioComponent(GameObject* Object, const std::string& AudioSignature, bool bIsLooping)
	: AudioPlayComponent(Object, AudioSignature)
{
	SetLooping(bIsLooping);
}

void BackgroundAudioComponent::Tick()
{
}