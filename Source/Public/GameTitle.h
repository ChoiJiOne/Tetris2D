#pragma once

#include "Color.h"
#include "Vector.hpp"
#include "GameObject.h"


/**
 * @brief ���� Ÿ��Ʋ�Դϴ�.
 */
class GameTitle : public GameObject
{
public:
	/**
	 * @brief ���� Ÿ��Ʋ�� �������Դϴ�.
	 * 
	 * @note Ÿ��Ʋ ���ڿ��� �ݵ�� �ƽ�Ű �ڵ� ���� ���� �ִ� ���ڵ�� �����Ǿ�� �մϴ�.
	 *
	 * @param Signature ���� Ÿ��Ʋ�� �ĺ����Դϴ�.
	 * @param Title ���� Ÿ��Ʋ�Դϴ�.
	 * @param FontSignature ���� Ÿ��Ʋ ���ڿ��� ��Ʈ �ñ״�ó�Դϴ�.
	 * @param Position ȭ�� ���� ���� Ÿ��Ʋ ��ġ�Դϴ�.
	 * @param Color Ÿ��Ʋ�� �����Դϴ�.
	 */
	GameTitle(
		const std::string& Signature, 
		const std::wstring& Title, 
		const std::string& FontSignature,
		const Vec2f& Position, 
		const LinearColor& Color
	);


	/**
	 * @brief ���� Ÿ��Ʋ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameTitle() {}


	/**
	 * @brief ���������� ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameTitle);


	/**
	 * @brief ���� Ÿ��Ʋ�� ������Ʈ�մϴ�.
	 * 
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


private:
	/**
	 * @brief ȭ�鿡 ǥ�õ� ���� Ÿ��Ʋ�Դϴ�.
	 */
	std::wstring Title_;


	/**
	 * @brief ���� Ÿ��Ʋ ���ڿ��� ��Ʈ �ñ״�ó�Դϴ�.
	 */
	std::string FontSignature_;


	/**
	 * @brief ȭ�鿡 ǥ�õ� ���� Ÿ��Ʋ�� �߽� ��ġ�Դϴ�.
	 */
	Vec2f Position_;


	/**
	 * @brief ȭ�鿡 ǥ�õ� ���� Ÿ��Ʋ�� �����Դϴ�.
	 */
	LinearColor Color_;
};