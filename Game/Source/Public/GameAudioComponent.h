#pragma once

#include "AudioPlayComponent.h"


/**
 * @brief ������ ������� �÷����ϴ� ������Ʈ�Դϴ�.
 */
class GameAudioComponent : public AudioPlayComponent
{
public:
	/**
	 * @brief ������ ������� �÷����ϴ� ������Ʈ�� �������Դϴ�.
	 * 
	 * @param Object �� ������Ʈ�� ������ ������Ʈ�� ������ ���Դϴ�.
	 * @param AudioSignature �÷����� ������� �ñ״�ó ���Դϴ�.
	 * @param bIsLooping �÷����� ������� �ݺ� �����Դϴ�.
	 */
	GameAudioComponent(GameObject* Object, const std::string& AudioSignature, bool bIsLooping);


	/**
	 * @brief ������ ������� �÷����ϴ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameAudioComponent() {}


	/**
	 * @brief ������Ʈ�� ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameAudioComponent);


	/**
	 * @brief ������ ������� �÷����ϴ� ������Ʈ�� ������Ʈ�մϴ�.
	 */
	virtual void Tick() override;
};