#pragma once

#include "Scene.h"


/**
 * @brief ��Ʈ���� ������ Ÿ��Ʋ ���Դϴ�.
 */
class TitleScene : public Scene
{
public:
	/**
	 * @brief ��Ʈ���� ������ Ÿ��Ʋ ���� �������Դϴ�.
	 */
	TitleScene();


	/**
	 * @brief ��Ʈ���� ������ Ÿ��Ʋ ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~TitleScene();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TitleScene);


	/**
	 * @brief Ÿ��Ʋ ���� ������Ʈ�մϴ�.
	 * 
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Update(float DeltaSeconds) override;


	/**
	 * @brief Ÿ��Ʋ ���� �����մϴ�.
	 */
	virtual void Reset() override;


private:
	/**
	 * @brief �� ���� ���� ������Ʈ�Դϴ�.
	 */
	std::vector<GameObject*> SceneObjects_;

};