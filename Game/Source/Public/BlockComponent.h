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
	 * @brief ��Ʈ���� ������ Ÿ���Դϴ�.
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
	 * @brief ���� ������Ʈ�� ������ ��Ʈ���� ������ �������Դϴ�.
	 * 
	 * @param Object �� ������Ʈ�� �����ϴ� ������Ʈ�� ������ ���Դϴ�.
	 * @param Center ������ �߽� ��ǥ�Դϴ�.
	 * @param Side ���簢�� ������ �� ���� �����Դϴ�.
	 * @param Type ������ Ÿ���Դϴ�.
	 */
	BlockComponent(GameObject* Object, const Vec2f& Center, const float& Side, const EType& Type)
		: AABBComponent(Object, Center, Side, Side)
		, Type_(Type) {}


	/**
	 * @brief ���� ������Ʈ�� ������ ��Ʈ���� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~BlockComponent() {}


	/**
	 * @brief ������Ʈ�� ���� ������ �� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(BlockComponent);


	/**
	 * @brief ��Ʈ���� ������ Ÿ���� ����ϴ�.
	 * 
	 * @return ��Ʈ���� ������ Ÿ���� ��ȯ�մϴ�.
	 */
	EType GetType() const { return Type_; }


	/**
	 * @brief ��Ʈ���� ���� Ÿ�Կ� �����ϴ� �ؽ�ó �ñ״�ó ���� ����ϴ�.
	 * 
	 * @return ��Ʈ���� ���� Ÿ�Կ� �����ϴ� �ؽ�ó �ñ״�ó ���� ��ȯ�մϴ�.
	 */
	const std::string& GetTypeTextureSignature() const { return TypeTextureSignatures_[Type_]; };
	

private:
	/**
	 * @brief ��Ʈ���� ������ Ÿ���Դϴ�.
	 */
	EType Type_ = EType::NONE;


	/**
	 * @brief ��Ʈ���� ������ Ÿ�Կ� �����ϴ� �ؽ�ó�� �ñ״�ó ���Դϴ�.
	 */
	static std::unordered_map<EType, std::string> TypeTextureSignatures_;
};