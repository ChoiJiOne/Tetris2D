#pragma once

#include <array>

#include "Scene.h"

class Button;


/**
 * @brief ���� ���� ���Դϴ�.
 */
class PauseScene : public Scene
{
public:
	/**
	 * @brief ���� ���� ������ ������ �� �ִ� �����Դϴ�.
	 */
	enum class ESelectState
	{
		NONE     = 0,
		CONTINUE = 1,
		RESET    = 2,
		QUIT     = 3,
	};


public:
	/**
	 * @brief ���� ���� ���� �������Դϴ�.
	 */
	PauseScene();


	/**
	 * @brief ���� ���� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~PauseScene();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PauseScene);


	/**
	 * @brief ���� ���� ���� ������Ʈ�մϴ�.
	 *
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief ���� ���� ���� ���� ���� ���¸� ����ϴ�.
	 *
	 * @return ���� ���� ���� ���� ���� ���¸� ��ȯ�մϴ�.
	 */
	ESelectState GetSelectState() const { return CurrentSelectState_; }


private:
	/**
	 * @brief ���� ���� ���� �����Դϴ�.
	 *
	 * @note ���� ���� ������ ��ȯ�� �߻��ϸ� �� ��ȯ �̺�Ʈ�� ����˴ϴ�.
	 */
	ESelectState CurrentSelectState_ = ESelectState::NONE;


	/**
	 * @brief ���� ���� ��ư�Դϴ�.
	 */
	std::array<Button*, 3> Buttons_;
};