#pragma once

#include "Color.h"
#include "Vector.hpp"
#include "GameObject.h"
#include "InputManager.h"

#include <functional>


/**
 * @brief �ؽ�Ʈ�� ���Ե� ��ư ������ �Ķ�����Դϴ�.
 * 
 * @note ��ư�� ǥ�õǴ� �ؽ�Ʈ�� UTF-16 ����Դϴ�.
 */
struct ButtonParamWithText
{
	const Vec2f& Position;
	const float& Width;
	const float& Height;
	const std::string& TextureSignature;
	const std::wstring& Text;
	const LinearColor& Color;
	const std::string& FontSignature;
	const EKeyCode& KeyCode;
	const std::function<void()>& ClickEvent;
	const float ReduceRate = 1.0f;
};


/**
 * @brief �ؽ�Ʈ�� ���Ե��� ���� ��ư ������ �Ķ�����Դϴ�.
 */
struct ButtonParamWithoutText
{
	const Vec2f& Position;
	const float& Width;
	const float& Height;
	const std::string& TextureSignature;
	const EKeyCode& KeyCode;
	const std::function<void()>& ClickEvent;
	const float ReduceRate = 1.0f;
};


/**
 * @brief ���� ���� �簢�� ��ư�Դϴ�.
 */
class Button : public GameObject
{
public:
	/**
	 * @brief ���� ���� �ؽ�Ʈ�� ���Ե� �簢�� ��ư Ŭ������ �������Դϴ�.
	 *
	 * @param Signature �簢�� ��ư�� �ñ״�ó ���Դϴ�.
	 * @param ConstructorParam ���� ���� �ؽ�Ʈ�� ���Ե� �簢�� ��ư Ŭ������ ���� �Ķ�����Դϴ�.
	 */
	Button(const std::string& Signature, const ButtonParamWithText& ConstructorParam);


	/**
	 * @brief ���� ���� �ؽ�Ʈ�� ���Ե� �簢�� ��ư Ŭ������ �������Դϴ�.
	 * 
	 * @note ��ư�� ǥ�õǴ� �ؽ�Ʈ�� UTF-16 ����Դϴ�.
	 * 
	 * @param Signature �簢�� ��ư�� �ñ״�ó ���Դϴ�.
	 * @param Position ���� ���� ��ư�� ��ġ�Դϴ�.
	 * @param Width ��ư�� ���� ũ���Դϴ�.
	 * @param Height ��ư�� ���� ũ���Դϴ�.
	 * @param TextureSignature ��ư�� �ؽ�ó �ñ״�ó�Դϴ�.
	 * @param Text ��ư�� ǥ�õ� �ؽ�Ʈ�Դϴ�.
	 * @param Color ��ư�� ǥ�õ� �ؽ�Ʈ�� �����Դϴ�.
	 * @param FontSignature ��ư�� ǥ�õ� �ؽ�Ʈ�� ��Ʈ �ñ״�ó�Դϴ�.
	 * @param KeyCode ��ư�� Ŭ������ �� ������ Ű �ڵ� ���Դϴ�.
	 * @param ClickEvent ��ư�� Ŭ������ �� ������ �̺�Ʈ�Դϴ�.
	 * @param ReduceRate ��ư�� Ŭ������ �� �پ�� �����Դϴ�. �⺻ ���� 1.0�Դϴ�.
	 */
	Button(
		const std::string& Signature,
		const Vec2f& Position,
		const float& Width,
		const float& Height,
		const std::string& TextureSignature,
		const std::wstring& Text,
		const LinearColor& Color,
		const std::string& FontSignature,
		const EKeyCode& KeyCode,
		const std::function<void()>& ClickEvent,
		const float ReduceRate = 1.0f
	);


	/**
	 * @brief ���� ���� �ؽ�Ʈ�� ���Ե��� ���� �簢�� ��ư Ŭ������ �������Դϴ�.
	 *
	 * @param Signature �簢�� ��ư�� �ñ״�ó ���Դϴ�.
	 * @param ConstructorParam ���� ���� �ؽ�Ʈ�� ���Ե��� ���� �簢�� ��ư Ŭ������ ���� �Ķ�����Դϴ�.
	 */
	Button(const std::string& Signature, const ButtonParamWithoutText& ConstructorParam);
	

	/**
	 * @brief ���� ���� �ؽ�Ʈ�� ���Ե��� ���� �簢�� ��ư Ŭ������ �������Դϴ�.
	 * 
	 * @param Signature �簢�� ��ư�� �ñ״�ó ���Դϴ�.
	 * @param Position ���� ���� ��ư�� ��ġ�Դϴ�.
	 * @param Width ��ư�� ���� ũ���Դϴ�.
	 * @param Height ��ư�� ���� ũ���Դϴ�.
	 * @param TextureSignature ��ư�� �ؽ�ó �ñ״�ó�Դϴ�.
	 * @param KeyCode ��ư�� Ŭ������ �� ������ Ű �ڵ� ���Դϴ�.
	 * @param ClickEvent ��ư�� Ŭ������ �� ������ �̺�Ʈ�Դϴ�.
	 * @param ReduceRate ��ư�� Ŭ������ �� �پ�� �����Դϴ�. �⺻ ���� 1.0�Դϴ�.
	 */
	Button(
		const std::string& Signature,
		const Vec2f& Position,
		const float& Width,
		const float& Height,
		const std::string& TextureSignature,
		const EKeyCode& KeyCode,
		const std::function<void()>& ClickEvent,
		const float ReduceRate = 1.0f
	);


	/**
	 * @brief ���� ���� ��ư Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Button();


	/**
	 * @brief ���������� ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Button);


	/**
	 * @brief ��ư�� ������Ʈ�մϴ�.
	 * 
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief ��ư�� ��ġ�� �����մϴ�.
	 * 
	 * @param Position ������ ��ư�� ��ġ�Դϴ�.
	 */
	void SetPosition(const Vec2f& Position) { Position_ = Position; }


private:
	/**
	 * @brief ���콺�� ���� ���� �ִ��� Ȯ���մϴ�.
	 * 
	 * @return ���콺�� ���� ���� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsDetectMouse() const;


private:
	/**
	 * @brief ���콺�� ��ư ���� �ִ��� Ȯ���մϴ�.
	 */
	bool bIsDetectMouse_ = false;


	/**
	 * @brief ��ư ���� �ؽ�Ʈ�� �ִ��� Ȯ���մϴ�.
	 */
	bool bIsTextMode_ = false;


	/**
	 * @brief ���� ���� �簢�� ��ư �߽� ��ǥ�Դϴ�.
	 */
	Vec2f Position_;


	/**
	 * @brief �簢�� ��ư�� ���� ũ���Դϴ�.
	 */
	float Width_ = 0.0f;


	/**
	 * @brief �簢�� ��ư�� ���� ũ���Դϴ�.
	 */
	float Height_ = 0.0f;


	/**
	 * @brief ��ư�� �ؽ�ó �ñ״�ó�Դϴ�.
	 */
	std::string TextureSignature_;


	/**
	 * @brief �簢�� ��ư�� �ؽ�Ʈ�Դϴ�.
	 * 
	 * @note �ؽ�Ʈ�� ���ٸ� ���õ˴ϴ�.
	 */
	std::wstring Text_;


	/**
	 * @brief �簢�� �ؽ�Ʈ�� �����Դϴ�.
	 * 
	 * @note �ؽ�Ʈ�� ���ٸ� ���õ˴ϴ�.
	 */
	LinearColor Color_;


	/**
	 * @brief �簢�� �ؽ�Ʈ�� ��Ʈ�Դϴ�.
	 */
	std::string FontSignature_;


	/**
	 * @brief ��ư�� �����ϴ� Ű �ڵ� ���Դϴ�.
	 */
	EKeyCode KeyCode_ = EKeyCode::CODE_NONE;


	/**
	 * @brief ��ư Ŭ�� �� �߻��� �̺�Ʈ�Դϴ�.
	 */
	std::function<void()> ClickEvent_ = nullptr;


	/**
	 * @brief ��ư Ŭ�� �� �پ��� ��ư�� �����Դϴ�.
	 */
	float ReduceRate_ = 0.0f;
};