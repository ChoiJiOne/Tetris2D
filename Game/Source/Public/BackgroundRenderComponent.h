#pragma once

#include "SpriteRenderComponent.h"


/**
 * @brief 백그라운드를 렌더링하는 컴포넌트입니다.
 */
class BackgroundRenderComponent : public SpriteRenderComponent
{
public:
	/**
	 * @brief 백그라운드를 렌더링하는 컴포넌트의 생성자입니다.
	 * 
	 * @param Object 이 컴포넌트를 소유하는 오브젝트의 포인터 값입니다.
	 * @param TextureSignature 스프라이트에 대응하는 백그라운드 텍스처의 시그니처 값입니다.
	 */
	BackgroundRenderComponent(GameObject* Object, const std::string& TextureSignature);



	/**
	 * @brief 백그라운드를 렌더링하는 컴포넌트의 가상 소멸자입니다.
	 */
	virtual ~BackgroundRenderComponent() {}



	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(BackgroundRenderComponent);


	/**
	 * @brief 백그라운드 스프라이트 렌더 컴포넌트를 업데이트합니다.
	 */
	virtual void Tick() override;
};