#include "BackgroundAudioComponent.h"
#include "Background.h"

BackgroundAudioComponent::BackgroundAudioComponent(GameObject* Object, const std::string& AudioSignature)
	: AudioPlayComponent(Object, AudioSignature)
{
}

void BackgroundAudioComponent::Tick()
{
	Background* Object = reinterpret_cast<Background*>(GetGameObject());

	if (Object->GetActiveAudio())
	{
		if (IsStopping() || IsDone())
		{
			Play();
		}
	}
}