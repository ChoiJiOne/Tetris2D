#pragma once

#include "Scene.h"

#include <vector>

class Button;


/**
 * @brief ��Ʈ���� ������ ���Դϴ�.
 */
class GameScene : public Scene
{
public:
	/**
	 * @brief ��Ʈ���� ���� ���� �⺻ �������Դϴ�.
	 */
	GameScene() = default;


	/**
	 * @brief ��Ʈ���� ���� ����  ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameScene() = default;


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameScene);


	/**
	 * @brief ��Ʈ���� ���� �� ���� ��ư�� ������Ʈ�մϴ�.
	 *
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


protected:
	/**
	 * @brief �� ���� ��ư�Դϴ�.
	 */
	std::vector<Button*> SceneButton_;
};