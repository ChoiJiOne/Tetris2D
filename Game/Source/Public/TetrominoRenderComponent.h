#pragma once

#include "GraphicsComponent.h"


/**
 * @brief ��Ʈ�ι̳븦 ȭ�鿡 �������ϴ� ������Ʈ�Դϴ�.
 */
class TetrominoRenderComponent : public GraphicsComponent
{
public:
	/**
	 * @brief ��Ʈ�ι̳븦 ȭ�鿡 �������ϴ� ������Ʈ�� �������Դϴ�.
	 */
	TetrominoRenderComponent(GameObject* Object);


	/**
	 * @brief ��Ʈ�ι̳븦 ȭ�鿡 �������ϴ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~TetrominoRenderComponent();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TetrominoRenderComponent);


	/**
	 * @brief ��Ʈ�ι̳븦 ȭ�鿡 �������ϴ� ������Ʈ�� ������Ʈ�մϴ�.
	 */
	void Tick();
};