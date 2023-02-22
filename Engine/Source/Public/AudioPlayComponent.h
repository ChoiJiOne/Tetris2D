#pragma once

#include "AudioComponent.h"


/**
 * @brief 오디오를 플레이하는 컴포넌트입니다.
 */
class AudioPlayComponent : public AudioComponent
{
public:
	/**
	 * @brief 게임 오브젝트가 소유한 오디오 플레이 컴포넌트 생성자 입니다.
	 * 
	 * @param Object 이 컴포넌트를 소유한 오브젝트의 포인터 값입니다.
	 * @param AudioSignature 플레이할 오디오의 시그니처 값입니다.
	 */
	AudioPlayComponent(GameObject* Object, const std::string& AudioSignature);


	/**
	 * @brief 게임 오브젝트가 소유한 오디오 플레이 컴포넌트의 가상 소멸자입니다.
	 */
	virtual ~AudioPlayComponent() {}


	/**
	 * @brief 컴포넌트의 복사 생성자 및 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(AudioPlayComponent);


	/**
	 * @brief 오디오 플레이 컴포넌트를 업데이트합니다.
	 */
	virtual void Tick();


	/**
	 * @brief 오디오의 크기를 설정합니다.
	 *
	 * @param Volume 오디오의 크기입니다. 범위는 0.0 ~ 1.0 입니다.
	 */
	void SetVolume(float Volume);


	/**
	 * @brief 현재 오디오의 크기를 얻습니다.
	 *
	 * @return 현재 오디오의 크기를 얻습니다.
	 */
	float GetVolume();


	/**
	 * @brief 오디오의 반복 여부를 설정합니다.
	 *
	 * @param bIsLoop 사운드 반복 여부입니다.
	 */
	void SetLooping(bool bIsLoop);


	/**
	 * @brief 오디오의 반복 여부를 얻습니다.
	 *
	 * @return 사운드가 반복한다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool GetLooping();


	/**
	 * @brief 오디오를 플레이합니다.
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
	 * @brief 오디오를 초기화합니다.
	 */
	void Reset();


private:
	/**
	 * @brief 오디오 리소스의 시그니처 값입니다.
	 */
	std::string AudioSignature_;
};