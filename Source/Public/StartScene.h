#pragma once

#include "Scene.h"


/**
 * @brief ���� ���� ���Դϴ�.
 */
class StartScene : public Scene
{
public:
	/**
	 * @brief ���� ���� ���� �⺻ �������Դϴ�.
	 */
	StartScene() = default;


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
};