#pragma once

#include <vector>

#include "GraphicsComponent.h"

class BlockComponent;


/**
 * @brief 보드를 화면에 렌더링하는 컴포넌트입니다.
 */
class BoardRenderComponent : public GraphicsComponent
{
public:
	/**
	 * @brief 보드를 화면에 렌더링하는 컴포넌트의 생성자입니다.
	 * 
	 * @param Object 이 컴포넌트를 소유한 게임 오브젝트의 포인터입니다.
	 */
	BoardRenderComponent(GameObject* Object);


	/**
	 * @brief 보드를 화면에 렌더링하는 컴포넌트의 가상 소멸자입니다.
	 */
	virtual ~BoardRenderComponent();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(BoardRenderComponent);


	/**
	 * @brief 보드를 화면에 렌더링하는 컴포넌트를 업데이트합니다.
	 */
	void Tick();


private:
	/**
	 * @brief 화면에 블럭을 렌더링합니다.
	 * 
	 * @param Blocks 화면에 그릴 블럭들입니다.
	 */
	void RenderBlocks(const std::vector<BlockComponent*>& Blocks);
};