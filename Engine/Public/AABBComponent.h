#pragma once

#include "BoundComponent.h"
#include "Vector.hpp"


/**
 * @brief 게임 오브젝트가 소유하는 AABB(축 정렬 경계 상자) 컴포넌트입니다.
 * +y
 * │    ┌───────────┐Max
 * │    │           │
 * │    │           │ ← AABB!
 * │    │           │
 * │ Min└───────────┘
 * │
 * ┼────────────────────────+x
 */
class AABBComponent : public BoundComponent
{
public:
	/**
	 * @brief 게임 오브젝트가 소유한 AABB 컴포넌트의 생성자입니다.
	 * 
	 * @param Object 이 컴포넌트를 소유하는 오브젝트의 포인터 값입니다.
	 * @param Center AABB의 중심 좌표입니다.
	 * @param Width AABB의 가로 크기입니다.
	 * @param Height AABB의 세로 크기입니다.
	 */
	AABBComponent(GameObject* Object, const Vec2f& Center, const float& Width, const float& Height)
		: BoundComponent(Object)
		, Center_(Center)
		, Width_(Width)
		, Height_(Height) {}


	/**
	 * @brief 게임 오브젝트가 소유한 AABB 컴포넌트의 가상 소멸자입니다.
	 */
	virtual ~AABBComponent() {}


	/**
	 * @brief 컴포넌트의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(AABBComponent);


	/**
	 * @brief 다른 AABB와의 충돌을 검사합니다.
	 * 
	 * @param BoundingBox 검사를 수행할 AABB입니다.
	 * 
	 * @return 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollision(const AABBComponent* BoundingBox);


	/**
	 * @brief AABB의 중심 좌표를 얻습니다.
	 * 
	 * @return AABB의 중심 좌표를 반환합니다.
	 */
	Vec2f GetCenter() const { return Center_; }


	/**
	 * @brief AABB의 중심 좌표를 설정합니다.
	 * 
	 * @param Center 설정할 중심 좌표입니다.
	 */
	void SetCenter(const Vec2f& Center) { Center_ = Center; }


	/**
	 * @brief AABB의 가로 크기를 얻습니다.
	 * 
	 * @return AABB의 가로 크기를 반환합니다.
	 */
	float GetWidth() const { return Width_; }


	/**
	 * @brief AABB의 가로 크기를 설정합니다.
	 * 
	 * @param Width 설정할 AABB의 가로 크기입니다.
	 */
	void SetWidth(float Width) { Width_ = Width; }


	/**
	 * @brief AABB의 세로 크기를 얻습니다.
	 *
	 * @return AABB의 세로 크기를 반환합니다.
	 */
	float GetHeight() const { return Height_; }


	/**
	 * @brief AABB의 세로 크기를 설정합니다.
	 *
	 * @param Height 설정할 AABB의 세로 크기입니다.
	 */
	void SetHeight(float Height) { Height_ = Height; }

	
private:
	/**
	 * @brief AABB의 LEFT BOTTON 위치를 얻습니다.
	 * 
	 * @note 아래 그림의 Min 좌표 값을 반환
	 * +y
	 * │    ┌───────────┐Max
	 * │    │           │
	 * │    │           │ ← AABB!
	 * │    │           │
	 * │ Min└───────────┘
	 * │ (이 값 반환!)
	 * ┼────────────────────────+x
	 */
	inline Vec2f GetMinPosition() const
	{
		return Vec2f(Center_.x - Width_ / 2.0f, Center_.y - Height_ / 2.0f);
	}


	/**
	 * @biref AABB의 RIGHT TOP의 위치를 얻습니다.
	 * 
	 * @note 아래 그림의 Max 좌표 값을 반환
	 * +y
	 * │    ┌───────────┐Max (이 값 반환!)
	 * │    │           │
	 * │    │           │ ← AABB!
	 * │    │           │
	 * │ Min└───────────┘
	 * │
	 * ┼────────────────────────+x
	 */
	inline Vec2f GetMaxPosition() const
	{
		return Vec2f(Center_.x + Width_ / 2.0f, Center_.y + Height_ / 2.0f);
	}


private:
	/**
	 * @brief AABB의 중심점입니다.
	 */
	Vec2f Center_;


	/**
	 * @brief AABB의 가로 크기입니다.
	 */
	float Width_ = 0.0f;


	/**
	 * @brief AABB의 세로 크기입니다.
	 */
	float Height_ = 0.0f;
};