#pragma once

#include <array>

#include "Scene.h"

class Button;


/**
 * @brief ���� ���� ���Դϴ�.
 */
class SettingScene : public Scene
{
public:
	/**
	 * @brief ���� ���� ������ ������ �� �ִ� �����Դϴ�.
	 */
	enum class ESelectState
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
	std::array<Button*, 11> Buttons_;
};