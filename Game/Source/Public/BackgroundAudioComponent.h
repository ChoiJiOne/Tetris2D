#pragma once

#include "AudioPlayComponent.h"


/**
 * @brief ��׶����� ������� �÷����ϴ� ������Ʈ�Դϴ�.
 */
class BackgroundAudioComponent : public AudioPlayComponent
{
public:
	/**
	 * @brief ��׶����� ������� �÷����ϴ� ������Ʈ�� �������Դϴ�.
	 * 
	 * @param Object �� ������Ʈ�� ������ ������Ʈ�� ������ ���Դϴ�.
	 * @param AudioSignature �÷����� ������� �ñ״�ó ���Դϴ�.
	 */
	BackgroundAudioComponent(GameObject* Object, const std::string& AudioSignature);


	/**
	 * @brief ��׶����� ������� �÷����ϴ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~BackgroundAudioComponent() {}


	/**
	 * @brief ������Ʈ�� ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(BackgroundAudioComponent);


	/**
	 * @brief ��׶����� ������� �÷����ϴ� ������Ʈ�� ������Ʈ�մϴ�.
	 */
	virtual void Tick() override;
};