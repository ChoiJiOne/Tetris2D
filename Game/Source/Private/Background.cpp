#include "Background.h"
#include "AudioPlayComponent.h"
#include "BackgroundRenderComponent.h"

Background::Background(
	const std::string& Signature,
	const std::string& TextureSignature,
	const std::string& AudioSignatire,
	bool bIsLooping
) : GameObject(Signature)
{
	AddComponent<AudioPlayComponent>("BackgroundAudio", AudioSignatire);
	AddComponent<BackgroundRenderComponent>("BackgroundRenderer", TextureSignature);

	GetComponent<AudioPlayComponent>("BackgroundAudio")->SetLooping(bIsLooping);
}

void Background::Tick(float DeltaSeconds)
{
	GetComponent<AudioPlayComponent>("BackgroundAudio")->Tick();
	GetComponent<BackgroundRenderComponent>("BackgroundRenderer")->Tick();
}

void Background::ResetAudio()
{
	AudioPlayComponent* BackgroundAudio = GetComponent<AudioPlayComponent>("BackgroundAudio");
	BackgroundAudio->Reset();
}

void Background::PlayAudio()
{
	bIsActive_ = true;
	
	AudioPlayComponent* BackgroundAudio = GetComponent<AudioPlayComponent>("BackgroundAudio");
	BackgroundAudio->Play();
}

void Background::StopAudio()
{
	bIsActive_ = false;

	AudioPlayComponent* BackgroundAudio = GetComponent<AudioPlayComponent>("BackgroundAudio");
	BackgroundAudio->Stop();
}

void Background::Voluble()
{
	AudioPlayComponent* BackgroundAudio = GetComponent<AudioPlayComponent>("BackgroundAudio");
	BackgroundAudio->SetVolume(1.0f);
}

void Background::Mute()
{
	AudioPlayComponent* BackgroundAudio = GetComponent<AudioPlayComponent>("BackgroundAudio");
	BackgroundAudio->SetVolume(0.0f);
}
