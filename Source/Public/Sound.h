#pragma once

#include "Macro.h"

#include <memory>

struct ma_engine;
struct ma_sound;


/**
 * @brief 플레이 가능한 사운드 리소스입니다.
 */
class Sound
{
public:
	/**
	 * @brief 사운드 리소스 생성자입니다.
	 * 
	 * @param AudioEngine 사운드 리소스를 생성할 때 사용할 miniaudio 엔진입니다.
	 * @param ResourcePath 사운드 파일의 파일 경로입니다.
	 * 
	 * @throws
	 * 사운드 파일 로딩에 실패하면 C++ 표준 예외를 던집니다.
	 * 사운드 리소스 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	Sound(ma_engine* AudioEngine, const std::string& ResourcePath);


	/**
	 * @brief 사운드 리소스 생성자의 가상 소멸자입니다.
	 */
	virtual ~Sound();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Sound);


	/**
	 * @brief 사운드의 크기를 설정합니다.
	 * 
	 * @param Volume 사운드의 크기입니다. 범위는 0.0 ~ 1.0 입니다.
	 */
	void SetVolume(float Volume);


	/**
	 * @brief 현재 사운드의 크기를 얻습니다.
	 * 
	 * @return 현재 사운드의 크기를 얻습니다.
	 */
	float GetVolume();


	/**
	 * @brief 사운드의 반복 여부를 설정합니다.
	 * 
	 * @param bIsLoop 사운드 반복 여부입니다.
	 */
	void SetLooping(bool bIsLoop);


	/**
	 * @brief 사운드의 반복 여부를 얻습니다.
	 * 
	 * @return 사운드가 반복한다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool GetLooping();


	/**
	 * @brief 사운드를 플레이합니다. 
	 * 
	 * @note 이전에 중지한 적이 있다면 중지한 시점부터 플레이됩니다.
	 */
	void Play();


	/**
	 * @brief 사운드가 플레이중인지 확인합니다.
	 * 
	 * @return 사운드가 플레이 중이라면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsPlaying();


	/**
	 * @brief 사운드 플레이가 끝났는지 확인합니다.
	 * 
	 * @return 사운드 플레이가 끝났다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsDone();


	/**
	 * @brief 사운드 플레이를 중지합니다.
	 */
	void Stop();


	/**
	 * @brief 사운드 플레이가 중지 되었는지 확인합니다.
	 * 
	 * @return 사운드 플레이가 중지 되었다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsStopping();


	/**
	 * @brief 사운드를 초기화합니다.
	 */
	void Reset();


private:
	/**
	 * @brief miniaudio 사운드 리소스의 포인터를 얻습니다.
	 * 
	 * @return miniaudio 사운드 리소스의 포인터를 반환합니다.
	 */
	ma_sound* GetSoundPrt() { return Sound_.get(); }


private:
	/**
	 * @brief miniaudio 사운드 리소스입니다.
	 */
	std::unique_ptr<ma_sound> Sound_ = nullptr;
};