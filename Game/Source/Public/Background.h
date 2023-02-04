#pragma once

#include "GameObject.h"


/**
 * @brief 백그라운드입니다.
 */
class Background : public GameObject
{
public:
	/**
	 * @brief 백그라운드의 생성자입니다.
	 *
	 * @param Signature 백그라운드의 식별자입니다.
	 * @param TextureSignature 백그라운드의 텍스처 시그니처 값입니다.
	 * @param AudioSignatire 백그라운드의 오디오 시그니처 값입니다.
	 */
	Background(
		const std::string& Signature,
		const std::string& TextureSignature,
		const std::string& AudioSignatire
	);


	/**
	 * @brief 백그라운드의 가상 소멸자입니다.
	 */
	virtual ~Background() {}


	/**
	 * @brief 명시적으로 복사 생성자외 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Background);


	/**
	 * @brief 백그라운드를 업데이트합니다.
	 *
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief 백그라운드 사운드를 초기화합니다.
	 */
	void ResetAudio();


	/**
	 * @brief 백그라운드 사운드를 활성화합니다.
	 */
	void ActiveAudio();


	/**
	 * @brief 백그라운드 사운드를 비활성화합니다.
	 */
	void InactiveAudio();


	/**
	 * @brief 백그라운드 사운드의 플레이 활성화 여부를 얻습니다.
	 * 
	 * @return 백그라운드 사운드의 플레이 활성화 여부를 반환합니다.
	 */
	bool GetActiveAudio() const { return bIsActive_; }


private:
	/**
	 * @brief 백그라운드 사운드의 플레이 활성화 여부입니다.
	 */
	bool bIsActive_ = false;
};