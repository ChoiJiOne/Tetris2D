#include "Background.h"
#include "BackgroundAudioComponent.h"
#include "BackgroundRenderComponent.h"

Background::Background(
	const std::string& Signature,
	const std::string& TextureSignature,
	const std::string& AudioSignatire
) : GameObject(Signature)
{
	AddComponent<BackgroundAudioComponent>("BackgroundAudio", AudioSignatire);
	AddComponent<BackgroundRenderComponent>("BackgroundRenderer", TextureSignature);
}

void Background::Tick(float DeltaSeconds)
{
	GetComponent<BackgroundAudioComponent>("BackgroundAudio")->Tick();
	GetComponent<BackgroundRenderComponent>("BackgroundRenderer")->Tick();
}

void Background::ResetAudio()
{
	BackgroundAudioComponent* BackgroundAudio = GetComponent<BackgroundAudioComponent>("BackgroundAudio");
	BackgroundAudio->Reset();
}

void Background::ActiveAudio()
{
	bIsActive_ = true;
	
	BackgroundAudioComponent* BackgroundAudio = GetComponent<BackgroundAudioComponent>("BackgroundAudio");
	BackgroundAudio->Play();
}

void Background::InactiveAudio()
{
	bIsActive_ = false;

	BackgroundAudioComponent* BackgroundAudio = GetComponent<BackgroundAudioComponent>("BackgroundAudio");
	BackgroundAudio->Stop();
}

void Background::Voluble()
{
	BackgroundAudioComponent* BackgroundAudio = GetComponent<BackgroundAudioComponent>("BackgroundAudio");
	BackgroundAudio->SetVolume(1.0f);
}

void Background::Mute()
{
	BackgroundAudioComponent* BackgroundAudio = GetComponent<BackgroundAudioComponent>("BackgroundAudio");
	BackgroundAudio->SetVolume(0.0f);
}
