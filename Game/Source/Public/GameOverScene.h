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


	/**
	 * @brief ������ �÷��� ������ �����մϴ�.
	 * 
	 * @param PlayTime ������ �÷����� �ð��Դϴ�.
	 * @param RemoveLine ������ ������ ���� ���Դϴ�.
	 * @param Level ������ �����Դϴ�.
	 */
	void SetUserInfo(const float& PlayTime, const int32_t& RemoveLine, const int32_t& Level)
	{
		PlayTime_ = PlayTime;
		RemoveLine_ = RemoveLine;
		Level_ = Level;
	}


private:
	/**
	 * @brief �� ���� ���� ������Ʈ�Դϴ�.
	 */
	std::vector<GameObject*> SceneObjects_;


	/**
	 * @brief ������ �÷��� �ð��Դϴ�.
	 */
	float PlayTime_ = 0.0f;


	/**
	 * @brief ���������� ���� ���Դϴ�.
	 */
	int32_t RemoveLine_ = 0;


	/**
	 * @brief ������ �����Դϴ�.
	 */
	int32_t Level_ = 0;
};