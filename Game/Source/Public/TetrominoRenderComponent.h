#pragma once

#include "GraphicsComponent.h"


/**
 * @brief 테트로미노를 화면에 렌더링하는 컴포넌트입니다.
 */
class TetrominoRenderComponent : public GraphicsComponent
{
public:
	/**
	 * @brief 테트로미노를 화면에 렌더링하는 컴포넌트의 생성자입니다.
	 */
	TetrominoRenderComponent(GameObject* Object);


	/**
	 * @brief 테트로미노를 화면에 렌더링하는 컴포넌트의 가상 소멸자입니다.
	 */
	virtual ~TetrominoRenderComponent();


	/**
	 * @brief 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(TetrominoRenderComponent);


	/**
	 * @brief 테트로미노를 화면에 렌더링하는 컴포넌트를 업데이트합니다.
	 */
	void Tick();
};