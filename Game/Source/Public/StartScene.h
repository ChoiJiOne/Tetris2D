#pragma once

#include "GameScene.h"


/**
 * @brief ���� ���� ���Դϴ�.
 */
class StartScene : public GameScene
{
public:
	/**
	 * @brief ���� ���� ���� �����Դϴ�.
	 */
	enum class EState
	{
		NONE    = 0,
		START   = 1,
		SETTING = 2,
		QUIT    = 3,
	};

	
public:
	/**
	 * @brief ���� ���� ���� �������Դϴ�.
	 */
	StartScene();


	/**
	 * @brief ���� ���� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~StartScene();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartScene);


	/**
	 * @brief ���� ���� ���� ������Ʈ�մϴ�.
	 *
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;

	
	/**
	 * @brief ���� ���� ���� ���� ���¸� ����ϴ�.
	 * 
	 * @return ���� ���� ���� ���� ���¸� ��ȯ�մϴ�.
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