#pragma once

#include <vector>

#include "GraphicsComponent.h"

class BlockComponent;


/**
 * @brief ���带 ȭ�鿡 �������ϴ� ������Ʈ�Դϴ�.
 */
class BoardRenderComponent : public GraphicsComponent
{
public:
	/**
	 * @brief ���带 ȭ�鿡 �������ϴ� ������Ʈ�� �������Դϴ�.
	 * 
	 * @param Object �� ������Ʈ�� ������ ���� ������Ʈ�� �������Դϴ�.
	 */
	BoardRenderComponent(GameObject* Object);


	/**
	 * @brief ���带 ȭ�鿡 �������ϴ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~BoardRenderComponent();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(BoardRenderComponent);


	/**
	 * @brief ���带 ȭ�鿡 �������ϴ� ������Ʈ�� ������Ʈ�մϴ�.
	 */
	void Tick();


private:
	/**
	 * @brief ȭ�鿡 ������ �������մϴ�.
	 * 
	 * @param Blocks ȭ�鿡 �׸� �������Դϴ�.
	 */
	void RenderBlocks(const std::vector<BlockComponent*>& Blocks);
};