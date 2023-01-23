#include "Sound.h"

#include <windows.h>
#include <algorithm>

// @third party code - BEGIN
#include <miniaudio/miniaudio.h>
// @third party code - END

Sound::Sound(ma_engine* AudioEngine, const std::string& ResourcePath)
{
	Sound_ = std::make_unique<ma_sound>();

	ma_result Result = ma_sound_init_from_file(AudioEngine, ResourcePath.c_str(), 0, nullptr, nullptr, GetSoundPrt());
	CHECK(Result == MA_SUCCESS, "failed to load sound resource");
}

Sound::~Sound()
{
	ma_sound_uninit(GetSoundPrt());
	Sound_.reset();
}

void Sound::SetVolume(float Volume)
{
	Volume = std::clamp<float>(Volume, 0.0f, 1.0f);
	ma_sound_set_volume(GetSoundPrt(), Volume);
}

float Sound::GetVolume()
{
	return ma_sound_get_volume(GetSoundPrt());
}

void Sound::SetLooping(bool bIsLoop)
{
	ma_sound_set_looping(GetSoundPrt(), static_cast<ma_bool32>(bIsLoop));
}

bool Sound::GetLooping()
{
	return ma_sound_is_looping(GetSoundPrt()) == MA_TRUE;
}

void Sound::Play()
{
	ma_result Result = ma_sound_start(GetSoundPrt());
	CHECK(Result == MA_SUCCESS, "failed to play sound");
}

bool Sound::IsPlaying()
{
	return ma_sound_is_playing(GetSoundPrt()) == MA_TRUE;
}

bool Sound::IsDone()
{
	return ma_sound_at_end(GetSoundPrt()) == MA_TRUE;
}

void Sound::Stop()
{
	ma_result Result = ma_sound_stop(GetSoundPrt());
	CHECK(Result == MA_SUCCESS, "failed to stop play sound");
}

bool Sound::IsStopping()
{
	return !IsDone() && !IsPlaying();
}

void Sound::Reset()
{
	ma_result Result = ma_sound_seek_to_pcm_frame(GetSoundPrt(), 0);
	CHECK(Result == MA_SUCCESS, "failed to reset play sound");
}
