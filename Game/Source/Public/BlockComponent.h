#pragma once

#include <unordered_map>

#include "AABBComponent.h"


/**
 * @brief 테트리스 게임의 블록 컴포넌트입니다.
 * 
 * @note 테트리스의 블록은 AABB기반입니다.
 */
class BlockComponent : public AABBComponent
{
public:
	/**
	 * @brief 테트리스 블럭의 상태입니다.
	 *
	 * @note 테트리스 블럭의 상태를 기반으로 충돌 처리 및 렌더링이 수행됩니다.
	 */
	enum class EState : int32_t
	{
		NONE  = 0,
		EMPTY = 1,
		FILL  = 2,
	};


	/**
	 * @brief 테트리스 블럭의 색상입니다.
	 */
	enum class EColor : int32_t
	{
		NONE   = 0,
		BLUE   = 1,
		CYAN   = 2,
		GRAY   = 3,
		GREEN  = 4,
		ORANGE = 5,
		PINK   = 6,
		PURPLE = 7,
		RED    = 8,
		YELLOW = 9
	};


public:
	/**
	 * @brief 게임 오브젝트가 소유한 테트리스 블럭의 컴포넌트 생성자입니다.
	 * 
	 * @param Object 이 컴포넌트를 소유하는 오브젝트의 포인터 값입니다.
	 * @param Center 테트리스 블럭의 중심 좌표입니다.
	 * @param Side 테트리스 블럭의 한 변의 길이입니다.
	 * @param Color 테트리스 블럭의 색상입니다.
	 * @param State 블럭의 상태입니다.
	 */
	BlockComponent(GameObject* Object, const Vec2f& Center, const float& Side, const EColor& Color, const EState& State)
		: AABBComponent(Object, Center, Side, Side)
		, State_(State) 
		, Color_(Color) {}


	/**
	 * @brief 게임 오브젝트가 소유한 테트리스 블럭의 가상 소멸자입니다.
	 */
	virtual ~BlockComponent() {}


	/**
	 * @brief 컴포넌트의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(BlockComponent);


	/**
	 * @brief 블럭의 충돌을 검사합니다.
	 * 
	 * @param BoundingBox 검사를 수행할 블럭입니다.
	 * 
	 * @return 충돌한다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsCollision(const BlockComponent* BoundingBox);


	/**
	 * @brief 테트리스 블럭의 크기를 얻습니다.
	 * 
	 * @return 테트리스 블럭의 크기를 반환합니다.
	 */
	float GetSide() const { return GetWidth(); }


	/**
	 * @brief 테트리스 블럭의 상태를 얻습니다.
	 * 
	 * @return 테트리스 블럭의 상태를 반환합니다.
	 */
	EState GetState() const { return State_; }


	/**
	 * @brief 테트리스 블럭의 상태를 설정합니다.
	 * 
	 * @param State 설정할 테트리스 블럭의 상태입니다.
	 */
	void SetState(const EState& State) { State_ = State; }


	/**
	 * @brief 테트리스 블럭의 색상을 얻습니다.
	 * 
	 * @return 테트리스 블럭의 색상을 반환합니다.
	 */
	EColor GetColor() const { return Color_; }


	/**
	 * @brief 테트리스 블럭의 색상을 설정합니다.
	 *
	 * @param State 설정할 테트리스 블럭의 색상입니다.
	 */
	void SetColor(const EColor& Color) { Color_ = Color; }


	/**
	 * @brief 테트리스 블럭 타입에 대응하는 텍스처 시그니처 값을 얻습니다.
	 * 
	 * @return 테트리스 블럭 타입에 대응하는 텍스처 시그니처 값을 반환합니다.
	 */
	const std::string& GetColorTextureSignature() const { return ColorTextureSignatures_[Color_]; };
	

private:
	/**
	 * @brief 테트리스 블럭의 상태입니다.
	 */
	EState State_ = EState::NONE;


	/**
	 * @brief 테트리스 블럭의 색상입니다.
	 */
	EColor Color_ = EColor::NONE;


	/**
	 * @brief 테트리스 블럭의 색상에 대응하는 텍스처의 시그니처 값입니다.
	 */
	static std::unordered_map<EColor, std::string> ColorTextureSignatures_;
};