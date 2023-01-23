#include "Sound.h"

#include <algorithm>

// @third party code - BEGIN
#include <miniaudio/miniaudio.h>
// @third party code - END

Sound::Sound(ma_engine* MiniaudioEngine, const std::string& ResourcePath)
{
	ma_result Result = ma_sound_init_from_file(MiniaudioEngine, ResourcePath.c_str(), 0, nullptr, nullptr, Sound_);
	CHECK(Result == MA_SUCCESS, "failed to load sound resource");
}

Sound::~Sound()
{
	ma_sound_uninit(Sound_);
}

void Sound::SetVolume(float Volume)
{
	Volume = std::clamp<float>(Volume, 0.0f, 1.0f);
	ma_sound_set_volume(Sound_, Volume);
}

float Sound::GetVolume()
{
	return ma_sound_get_volume(Sound_);
}

void Sound::Play()
{
	ma_result Result = ma_sound_start(Sound_);
	CHECK(Result == MA_SUCCESS, "failed to play sound");
}

void Sound::Start()
{
}

void Sound::Stop()
{
	ma_result Result = ma_sound_stop(Sound_);
	CHECK(Result == MA_SUCCESS, "failed to stop play sound");
}
