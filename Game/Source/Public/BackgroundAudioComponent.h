#pragma once

#include "AudioPlayComponent.h"


/**
 * @brief 백그라운드의 오디오를 플레이하는 컴포넌트입니다.
 */
class BackgroundAudioComponent : public AudioPlayComponent
{
public:
	/**
	 * @brief 백그라운드의 오디오를 플레이하는 컴포넌트의 생성자입니다.
	 * 
	 * @param Object 이 컴포넌트를 소유한 오브젝트의 포인터 값입니다.
	 * @param AudioSignature 플레이할 오디오의 시그니처 값입니다.
	 */
	BackgroundAudioComponent(GameObject* Object, const std::string& AudioSignature);


	/**
	 * @brief 백그라운드의 오디오를 플레이하는 컴포넌트의 가상 소멸자입니다.
	 */
	virtual ~BackgroundAudioComponent() {}


	/**
	 * @brief 컴포넌트의 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(BackgroundAudioComponent);


	/**
	 * @brief 백그라운드의 오디오를 플레이하는 컴포넌트를 업데이트합니다.
	 */
	virtual void Tick() override;
};