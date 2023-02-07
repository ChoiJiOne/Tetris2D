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
	 * @brief 테트리스 블럭의 타입입니다.
	 */
	enum class EType : int32_t
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
	 * @brief 게임 오브젝트가 소유한 테트리스 블럭의 생성자입니다.
	 * 
	 * @param Object 이 컴포넌트를 소유하는 오브젝트의 포인터 값입니다.
	 * @param Center 블럭의 중심 좌표입니다.
	 * @param Side 정사각형 블럭의 한 변의 길이입니다.
	 * @param Type 블럭의 타입입니다.
	 */
	BlockComponent(GameObject* Object, const Vec2f& Center, const float& Side, const EType& Type)
		: AABBComponent(Object, Center, Side, Side)
		, Type_(Type) {}


	/**
	 * @brief 게임 오브젝트가 소유한 테트리스 블럭의 가상 소멸자입니다.
	 */
	virtual ~BlockComponent() {}


	/**
	 * @brief 컴포넌트의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(BlockComponent);


	/**
	 * @brief 테트리스 블럭의 타입을 얻습니다.
	 * 
	 * @return 테트리스 블럭의 타입을 반환합니다.
	 */
	EType GetType() const { return Type_; }


	/**
	 * @brief 테트리스 블럭 타입에 대응하는 텍스처 시그니처 값을 얻습니다.
	 * 
	 * @return 테트리스 블럭 타입에 대응하는 텍스처 시그니처 값을 반환합니다.
	 */
	const std::string& GetTypeTextureSignature() const { return TypeTextureSignatures_[Type_]; };
	

private:
	/**
	 * @brief 테트리스 블럭의 타입입니다.
	 */
	EType Type_ = EType::NONE;


	/**
	 * @brief 테트리스 블럭의 타입에 대응하는 텍스처의 시그니처 값입니다.
	 */
	static std::unordered_map<EType, std::string> TypeTextureSignatures_;
};