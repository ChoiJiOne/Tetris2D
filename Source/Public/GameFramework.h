#pragma once

#include "Macro.h"


/**
 * @brief ������ �ʱ�ȭ �� �����ϴ� �����ӿ�ũ�Դϴ�.
 * 
 * @note ������ �����Ǵ� Ŭ������ �� �����ӿ�ũ�� �ݵ�� ��ӹ޾ƾ� �մϴ�.
 */
class GameFramework
{
public:
	/**
	 * @brief ���� �����ӿ�ũ�� �������Դϴ�.
	 * 
	 * @note �� �����ڴ� �ƹ��� �ʱ�ȭ�� �������� �ʽ��ϴ�.
	 */
	GameFramework() = default;


	/**
	 * @brief ���� �����ӿ�ũ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameFramework();


	/**
	 * @brief ���� �����ӿ�ũ�� �ʱ�ȭ�մϴ�.
	 * 
	 * @note ���� �Լ���, �ݵ�� ���� Ŭ�������� �����ؾ� �մϴ�.
	 */
	virtual void Init() = 0;


	/**
	 * @brief ���� �����ӿ�ũ�� �����մϴ�.
	 * 
	 * @note ���� �Լ���, �ݵ�� ���� Ŭ�������� �����ؾ� �մϴ�.
	 */
	virtual void Run() = 0;
};