#pragma once

#include "GameScene.h"


/**
 * @brief ���� ���� ���Դϴ�.
 */
class SettingScene : public GameScene
{
public:
	/**
	 * @brief ���� ���� ���� �����Դϴ�.
	 */
	enum class EState
	{
		NONE = 0,
		BACK = 1,
	};


public:
	/**
	 * @brief ���� ���� ���� �������Դϴ�.
	 */
	SettingScene();


	/**
	 * @brief ���� ���� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~SettingScene();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(SettingScene);


	/**
	 * @brief ���� ���� ���� ������Ʈ�մϴ�.
	 *
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief ���� ���� ���� ���¸� ����ϴ�.
	 *
	 * @return ���� ���� ���� ���¸� ��ȯ�մϴ�.
	 */
	EState GetCurrentState() const { return CurrentState_; }


private:
	/**
	 * @brief ���� ���� ���� �����Դϴ�.
	 *
	 * @note ���� ���� ������ ��ȯ�� �߻��ϸ� �� ��ȯ �̺�Ʈ�� ����˴ϴ�.
	 */
	EState CurrentState_ = EState::NONE;
};