#pragma once

#include "Color.h"
#include "Vector.hpp"
#include "GameObject.h"


/**
 * @brief ���� ���� �ؽ�Ʈ ������Ʈ�Դϴ�.
 */
class GameText : public GameObject
{
public:
	/**
	 * @brief ���� ���� �ؽ�Ʈ �������Դϴ�.
	 * 
	 * @note �ؽ�Ʈ ���ڿ��� �ݵ�� �ƽ�Ű �ڵ� ���� ���� �ִ� ���ڵ�� �����Ǿ�� �մϴ�.
	 *
	 * @param Signature ���� �ؽ�Ʈ�� �ĺ����Դϴ�.
	 * @param Text ���� �ؽ�Ʈ�Դϴ�.
	 * @param FontSignature ���� �ؽ�Ʈ�� ���ڿ��� ��Ʈ �ñ״�ó�Դϴ�.
	 * @param Position ���� ���� ���� �ؽ�Ʈ ��ġ�Դϴ�.
	 * @param Color �ؽ�Ʈ�� �����Դϴ�.
	 */
	GameText(
		const std::string& Signature, 
		const std::wstring& Text, 
		const std::string& FontSignature,
		const Vec2f& Position, 
		const LinearColor& Color
	);


	/**
	 * @brief ���� Ÿ��Ʋ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameText() {}


	/**
	 * @brief ���������� ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameText);


	/**
	 * @brief ���� �ؽ�Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief ���� ���� ���� �ؽ�Ʈ ��ġ�� �����մϴ�.
	 *  
	 * @param Position ������ ���� �ؽ�Ʈ�� ��ġ�Դϴ�.
	 */
	void SetPosition(const Vec2f& Position) { Position_ = Position; }


	/**
	 * @brief ���� �ؽ�Ʈ�� �����մϴ�.
	 *
	 * @note �ؽ�Ʈ ���ڿ��� �ݵ�� �ƽ�Ű �ڵ� ���� ���� �ִ� ���ڵ�� �����Ǿ�� �մϴ�.
	 *
	 * @param Text ������ ���� �ؽ�Ʈ�Դϴ�.
	 */
	void SetText(const std::wstring& Text) { Text_ = Text; }


	/**
	 * @brief ���� �ؽ�Ʈ�� ������ �����մϴ�.
	 * 
	 * @param Color ������ ���� �ؽ�Ʈ�� �����Դϴ�.
	 */
	void SetColor(const LinearColor& Color) { Color_ = Color; }


private:
	/**
	 * @brief ȭ�鿡 ǥ�õ� ���� �ؽ�Ʈ�Դϴ�.
	 */
	std::wstring Text_;


	/**
	 * @brief ���� �ؽ�Ʈ ���ڿ��� ��Ʈ �ñ״�ó�Դϴ�.
	 */
	std::string FontSignature_;


	/**
	 * @brief ���� �� ǥ�õ� ���� �ؽ�Ʈ�� �߽� ��ġ�Դϴ�.
	 */
	Vec2f Position_;


	/**
	 * @brief ���忡 ǥ�õ� ���� �ؽ�Ʈ �����Դϴ�.
	 */
	LinearColor Color_;
};