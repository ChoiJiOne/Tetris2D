#pragma once

#include "Macro.h"

#include <functional>


/**
 * @brief ���� ���� �����մϴ�.
 */
class Scene
{
public:
	/**
	 * @brief ���� ���� �⺻ �������Դϴ�.
	 */
	Scene() = default;


	/**
	 * @brief ���� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Scene() = default;


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Scene);


	/**
	 * @brief ���� ���� ������Ʈ�մϴ�.
	 * 
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) = 0;


	/**
	 * @brief �� ��ȯ�� �߻����� ��, ������ �̺�Ʈ�� �����մϴ�.
	 */
	void SetSwitchEvent(const std::function<void()>& SwitchEvent) { SwitchEvent_ = SwitchEvent; }


protected:
	/**
	 * @brief �� ��ȯ�� �߻����� ��, �̺�Ʈ�� �����մϴ�.
	 */
	void RunSwitchEvent()
	{
		if (SwitchEvent_) SwitchEvent_();
	}


private:
	/**
	 * @brief �� ��ȯ�� �߻����� ��, ������ �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> SwitchEvent_;
};