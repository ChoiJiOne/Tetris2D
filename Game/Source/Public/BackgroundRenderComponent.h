#pragma once

#include "SpriteRenderComponent.h"


/**
 * @brief ��׶��带 �������ϴ� ������Ʈ�Դϴ�.
 */
class BackgroundRenderComponent : public SpriteRenderComponent
{
public:
	/**
	 * @brief ��׶��带 �������ϴ� ������Ʈ�� �������Դϴ�.
	 * 
	 * @param Object �� ������Ʈ�� �����ϴ� ������Ʈ�� ������ ���Դϴ�.
	 * @param TextureSignature ��������Ʈ�� �����ϴ� ��׶��� �ؽ�ó�� �ñ״�ó ���Դϴ�.
	 */
	BackgroundRenderComponent(GameObject* Object, const std::string& TextureSignature);



	/**
	 * @brief ��׶��带 �������ϴ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~BackgroundRenderComponent() {}



	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(BackgroundRenderComponent);


	/**
	 * @brief ��׶��� ��������Ʈ ���� ������Ʈ�� ������Ʈ�մϴ�.
	 */
	virtual void Tick() override;
};