#include "Background.h"
#include "GameAudioComponent.h"
#include "BackgroundRenderComponent.h"

Background::Background(
	const std::string& Signature,
	const std::string& TextureSignature,
	const std::string& AudioSignatire,
	bool bIsLooping
) : GameObject(Signature)
{
	AddComponent<GameAudioComponent>("BackgroundAudio", AudioSignatire, bIsLooping);
	AddComponent<BackgroundRenderComponent>("BackgroundRenderer", TextureSignature);
}

void Background::Tick(float DeltaSeconds)
{
	GetComponent<GameAudioComponent>("BackgroundAudio")->Tick();
	GetComponent<BackgroundRenderComponent>("BackgroundRenderer")->Tick();
}

void Background::ResetAudio()
{
	GameAudioComponent* BackgroundAudio = GetComponent<GameAudioComponent>("BackgroundAudio");
	BackgroundAudio->Reset();
}

void Background::PlayAudio()
{
	bIsActive_ = true;
	
	GameAudioComponent* BackgroundAudio = GetComponent<GameAudioComponent>("BackgroundAudio");
	BackgroundAudio->Play();
}

void Background::StopAudio()
{
	bIsActive_ = false;

	GameAudioComponent* BackgroundAudio = GetComponent<GameAudioComponent>("BackgroundAudio");
	BackgroundAudio->Stop();
}

void Background::Voluble()
{
	GameAudioComponent* BackgroundAudio = GetComponent<GameAudioComponent>("BackgroundAudio");
	BackgroundAudio->SetVolume(1.0f);
}

void Background::Mute()
{
	GameAudioComponent* BackgroundAudio = GetComponent<GameAudioComponent>("BackgroundAudio");
	BackgroundAudio->SetVolume(0.0f);
}
