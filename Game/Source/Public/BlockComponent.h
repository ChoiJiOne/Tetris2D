#pragma once

#include <unordered_map>

#include "AABBComponent.h"


/**
 * @brief ��Ʈ���� ������ ���� ������Ʈ�Դϴ�.
 * 
 * @note ��Ʈ������ ������ AABB����Դϴ�.
 */
class BlockComponent : public AABBComponent
{
public:
	/**
	 * @brief ��Ʈ���� ������ �����Դϴ�.
	 *
	 * @note ��Ʈ���� ������ ���¸� ������� �浹 ó�� �� �������� ����˴ϴ�.
	 */
	enum class EState : int32_t
	{
		NONE  = 0,
		EMPTY = 1,
		FILL  = 2,
	};


	/**
	 * @brief ��Ʈ���� ������ �����Դϴ�.
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
	 * @brief ���� ������Ʈ�� ������ ��Ʈ���� ������ ������Ʈ �������Դϴ�.
	 * 
	 * @param Object �� ������Ʈ�� �����ϴ� ������Ʈ�� ������ ���Դϴ�.
	 * @param Center ��Ʈ���� ������ �߽� ��ǥ�Դϴ�.
	 * @param Side ��Ʈ���� ������ �� ���� �����Դϴ�.
	 * @param Color ��Ʈ���� ������ �����Դϴ�.
	 * @param State ������ �����Դϴ�.
	 */
	BlockComponent(GameObject* Object, const Vec2f& Center, const float& Side, const EColor& Color, const EState& State)
		: AABBComponent(Object, Center, Side, Side)
		, State_(State) 
		, Color_(Color) {}


	/**
	 * @brief ���� ������Ʈ�� ������ ��Ʈ���� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~BlockComponent() {}


	/**
	 * @brief ������Ʈ�� ���� ������ �� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(BlockComponent);


	/**
	 * @brief ������ �浹�� �˻��մϴ�.
	 * 
	 * @param BoundingBox �˻縦 ������ �����Դϴ�.
	 * 
	 * @return �浹�Ѵٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsCollision(const BlockComponent* BoundingBox);


	/**
	 * @brief ��Ʈ���� ������ ũ�⸦ ����ϴ�.
	 * 
	 * @return ��Ʈ���� ������ ũ�⸦ ��ȯ�մϴ�.
	 */
	float GetSide() const { return GetWidth(); }


	/**
	 * @brief ��Ʈ���� ������ ���¸� ����ϴ�.
	 * 
	 * @return ��Ʈ���� ������ ���¸� ��ȯ�մϴ�.
	 */
	EState GetState() const { return State_; }


	/**
	 * @brief ��Ʈ���� ������ ���¸� �����մϴ�.
	 * 
	 * @param State ������ ��Ʈ���� ������ �����Դϴ�.
	 */
	void SetState(const EState& State) { State_ = State; }


	/**
	 * @brief ��Ʈ���� ������ ������ ����ϴ�.
	 * 
	 * @return ��Ʈ���� ������ ������ ��ȯ�մϴ�.
	 */
	EColor GetColor() const { return Color_; }


	/**
	 * @brief ��Ʈ���� ������ ������ �����մϴ�.
	 *
	 * @param State ������ ��Ʈ���� ������ �����Դϴ�.
	 */
	void SetColor(const EColor& Color) { Color_ = Color; }


	/**
	 * @brief ��Ʈ���� ���� Ÿ�Կ� �����ϴ� �ؽ�ó �ñ״�ó ���� ����ϴ�.
	 * 
	 * @return ��Ʈ���� ���� Ÿ�Կ� �����ϴ� �ؽ�ó �ñ״�ó ���� ��ȯ�մϴ�.
	 */
	const std::string& GetColorTextureSignature() const { return ColorTextureSignatures_[Color_]; };
	

private:
	/**
	 * @brief ��Ʈ���� ������ �����Դϴ�.
	 */
	EState State_ = EState::NONE;


	/**
	 * @brief ��Ʈ���� ������ �����Դϴ�.
	 */
	EColor Color_ = EColor::NONE;


	/**
	 * @brief ��Ʈ���� ������ ���� �����ϴ� �ؽ�ó�� �ñ״�ó ���Դϴ�.
	 */
	static std::unordered_map<EColor, std::string> ColorTextureSignatures_;
};