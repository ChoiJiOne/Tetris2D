#pragma once

#include "Macro.h"


/**
 * @brief ���� ������ ����� �ý����� �������̽� Ŭ�����Դϴ�.
 */
class ISystem
{
public:
	/**
	 * @brief ���� ������ ����� �ý����� �������̽� Ŭ���� �������Դϴ�.
	 */
	ISystem() = default;


	/**
	 * @brief ���� ������ ����� �ý����� �������̽� Ŭ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ISystem() {}


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ISystem);
};