#pragma once

#include "Vector.hpp"
#include "GraphicsComponent.h"


/**
 * @brief 스프라이트를 렌더링하는 컴포넌트입니다.
 */
class SpriteRenderComponent : public GraphicsComponent
{
public:
	/**
	 * @brief 게임 오브젝트가 소유한 스프라이트 렌더 컴포넌트의 생성자입니다.
	 *
	 * @param Object 이 컴포넌트를 소유하는 오브젝트의 포인터 값입니다.
	 * @param TextureSignature 스프라이트에 대응하는 텍스처의 시그니처 값입니다.
	 * @param Position 스프라이트의 중심 좌표입니다.
	 * @param Width 스프라이트의 가로 크기입니다.
	 * @param Height 스프라이트의 세로 크기입니다.
	 */
	SpriteRenderComponent(
		GameObject* Object,
		const std::string& TextureSignature,
		const Vec2f& Position,
		const float& Width,
		const float& Height
	) : GraphicsComponent(Object),
		TextureSignature_(TextureSignature),
		Position_(Position),
		Width_(Width),
		Height_(Height)
	{
	}


	/**
	 * @brief 게임 오브젝트가 소유하는 스프라이트 렌더 컴포넌트의 가상 소멸자입니다.
	 */
	virtual ~SpriteRenderComponent() {}


	/**
	 * @brief 컴포넌트의 복사 생성자 및 대입연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(SpriteRenderComponent);


	/**
	 * @brief 스프라이트 렌더 컴포넌트를 업데이트합니다.
	 */
	virtual void Tick();


	/**
	 * @brief 스프라이트에 대응하는 텍스처의 시그니처 값을 설정합니다.
	 * 
	 * @param TextureSignature 설정할 텍스처 시그니처 값입니다.
	 */
	void SetTextureSignature(const std::string& TextureSignature) { TextureSignature_ = TextureSignature; }


	/**
	 * @brief 스프라이트의 중심 좌표를 설정합니다
	 * 
	 * @param Position 설정할 스프라이트의 중심 좌표입니다.
	 */
	void SetPosition(const Vec2f& Position) { Position_ = Position; }


	/**
	 * @brief 스프라이트의 가로 크기를 설정합니다.
	 * 
	 * @param Width 설정할 스프라이트의 가로 크기입니다.
	 */
	void SetWidth(const float& Width) { Width_ = Width; }


	/**
	 * @brief 스프라이트의 세로 크기를 설정합니다.
	 * 
	 * @param Width 설정할 스프라이트의 세로 크기입니다.
	 */
	void SetHeight(const float& Height) { Height_ = Height; }


private:
	/**
	 * @brief 스프라이트에 대응하는 텍스처의 시그니처 값입니다.
	 */
	std::string TextureSignature_;


	/**
	 * @brief 스프라이트의 중심 좌표입니다.
	 */
	Vec2f Position_;


	/**
	 * @brief 스프라이트의 가로 크기입니다.
	 */
	float Width_;


	/**
	 * @brief 스프라이트의 세로 크기입니다.
	 */
	float Height_;
};