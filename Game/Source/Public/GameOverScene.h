#pragma once

#include "Scene.h"

#include <vector>

class GameObject;


/**
 * @brief ��Ʈ���� ������ ���� ���Դϴ�.
 */
class GameOverScene : public Scene
{
public:
	/**
	 * @brief ��Ʈ���� ������ ���� ���� �������Դϴ�.
	 */
	GameOverScene();


	/**
	 * @brief ��Ʈ���� ������ ���� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameOverScene();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameOverScene);


	/**
	 * @brief ���� ���� ������Ʈ�մϴ�.
	 * 
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Update(float DeltaSeconds) override;


	/**
	 * @brief ���� ���� �����մϴ�.
	 */
	virtual void Reset() override;
};