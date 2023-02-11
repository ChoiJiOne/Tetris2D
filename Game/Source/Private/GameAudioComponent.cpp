#include "GameAudioComponent.h"
#include "Background.h"

GameAudioComponent::GameAudioComponent(GameObject* Object, const std::string& AudioSignature, bool bIsLooping)
	: AudioPlayComponent(Object, AudioSignature)
{
	SetLooping(bIsLooping);
}

void GameAudioComponent::Tick()
{
}