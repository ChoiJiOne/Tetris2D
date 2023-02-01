#pragma once

#include "Color.h"
#include "Vector.hpp"
#include "GameObject.h"
#include "InputManager.h"

#include <functional>


/**
 * @brief 텍스트가 포함된 버튼 생성자 파라미터입니다.
 * 
 * @note 버튼에 표시되는 텍스트는 UTF-16 기반입니다.
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
	const bool bIsMouseMode = true;
};


/**
 * @brief 텍스트가 포함되지 않은 버튼 생성자 파라미터입니다.
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
	const bool bIsMouseMode = true;
};


/**
 * @brief 게임 내의 사각형 버튼입니다.
 */
class Button : public GameObject
{
public:
	/**
	 * @brief 게임 내의 텍스트가 포함된 사각형 버튼 클래스의 생성자입니다.
	 *
	 * @param Signature 사각형 버튼의 시그니처 값입니다.
	 * @param ConstructorParam 게임 내의 텍스트가 포함된 사각형 버튼 클래스의 생성 파라미터입니다.
	 */
	Button(const std::string& Signature, const ButtonParamWithText& ConstructorParam);


	/**
	 * @brief 게임 내의 텍스트가 포함된 사각형 버튼 클래스의 생성자입니다.
	 * 
	 * @note 버튼에 표시되는 텍스트는 UTF-16 기반입니다.
	 * 
	 * @param Signature 사각형 버튼의 시그니처 값입니다.
	 * @param Position 월드 상의 버튼의 위치입니다.
	 * @param Width 버튼의 가로 크기입니다.
	 * @param Height 버튼의 세로 크기입니다.
	 * @param TextureSignature 버튼의 텍스처 시그니처입니다.
	 * @param Text 버튼에 표시될 텍스트입니다.
	 * @param Color 버튼에 표시될 텍스트의 색상입니다.
	 * @param FontSignature 버튼에 표시될 텍스트의 폰트 시그니처입니다.
	 * @param KeyCode 버튼이 클릭됐을 때 실행할 키 코드 값입니다.
	 * @param ClickEvent 버튼이 클릭됐을 때 실행할 이벤트입니다.
	 * @param ReduceRate 버튼이 클릭됐을 때 줄어들 비율입니다. 기본 값은 1.0입니다.
	 * @param bIsMouseMode 버튼에 마우스를 감지하는 모드인지 확인합니다. 기본적으로 확인합니다.
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
		const float ReduceRate = 1.0f,
		bool bIsMouseMode = true
	);


	/**
	 * @brief 게임 내의 텍스트가 포함되지 않은 사각형 버튼 클래스의 생성자입니다.
	 *
	 * @param Signature 사각형 버튼의 시그니처 값입니다.
	 * @param ConstructorParam 게임 내의 텍스트가 포함되지 않은 사각형 버튼 클래스의 생성 파라미터입니다.
	 */
	Button(const std::string& Signature, const ButtonParamWithoutText& ConstructorParam);
	

	/**
	 * @brief 게임 내의 텍스트가 포함되지 않은 사각형 버튼 클래스의 생성자입니다.
	 * 
	 * @param Signature 사각형 버튼의 시그니처 값입니다.
	 * @param Position 월드 상의 버튼의 위치입니다.
	 * @param Width 버튼의 가로 크기입니다.
	 * @param Height 버튼의 세로 크기입니다.
	 * @param TextureSignature 버튼의 텍스처 시그니처입니다.
	 * @param KeyCode 버튼이 클릭됐을 때 실행할 키 코드 값입니다.
	 * @param ClickEvent 버튼이 클릭됐을 때 실행할 이벤트입니다.
	 * @param ReduceRate 버튼이 클릭됐을 때 줄어들 비율입니다. 기본 값은 1.0입니다.
	 * @param bIsMouseMode 버튼에 마우스를 감지하는 모드인지 확인합니다. 기본적으로 확인합니다.
	 */
	Button(
		const std::string& Signature,
		const Vec2f& Position,
		const float& Width,
		const float& Height,
		const std::string& TextureSignature,
		const EKeyCode& KeyCode,
		const std::function<void()>& ClickEvent,
		const float ReduceRate = 1.0f,
		bool bIsMouseMode = true
	);


	/**
	 * @brief 게임 내의 버튼 클래스의 가상 소멸자입니다.
	 */
	virtual ~Button();


	/**
	 * @brief 명시적으로 복사 생성자외 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Button);


	/**
	 * @brief 버튼을 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief 버튼의 위치를 설정합니다.
	 * 
	 * @param Position 설정할 버튼의 위치입니다.
	 */
	void SetPosition(const Vec2f& Position) { Position_ = Position; }


private:
	/**
	 * @brief 마우스가 범위 내에 있는지 확인합니다.
	 * 
	 * @return 마우스가 범위 내에 있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsDetectMouse() const;


private:
	/**
	 * @brief 마우스가 버튼 내에 있는지 확인합니다.
	 */
	bool bIsDetectMouse_ = false;


	/**
	 * @brief 버튼 내에 텍스트가 있는지 확인합니다.
	 */
	bool bIsTextMode_ = false;


	/**
	 * @brief 월드 상의 사각형 버튼 중심 좌표입니다.
	 */
	Vec2f Position_;


	/**
	 * @brief 사각형 버튼의 가로 크기입니다.
	 */
	float Width_ = 0.0f;


	/**
	 * @brief 사각형 버튼의 세로 크기입니다.
	 */
	float Height_ = 0.0f;


	/**
	 * @brief 버튼의 텍스처 시그니처입니다.
	 */
	std::string TextureSignature_;


	/**
	 * @brief 사각형 버튼의 텍스트입니다.
	 * 
	 * @note 텍스트가 없다면 무시됩니다.
	 */
	std::wstring Text_;


	/**
	 * @brief 사각형 텍스트의 색상입니다.
	 * 
	 * @note 텍스트가 없다면 무시됩니다.
	 */
	LinearColor Color_;


	/**
	 * @brief 사각형 텍스트의 폰트입니다.
	 */
	std::string FontSignature_;


	/**
	 * @brief 버튼에 대응하는 키 코드 값입니다.
	 */
	EKeyCode KeyCode_ = EKeyCode::CODE_NONE;


	/**
	 * @brief 버튼 클릭 시 발생할 이벤트입니다.
	 */
	std::function<void()> ClickEvent_ = nullptr;


	/**
	 * @brief 버튼 클릭 시 줄어드는 버튼의 비율입니다.
	 */
	float ReduceRate_ = 0.0f;


	/**
	 * @brief 버튼이 마우스를 감지하는 모드인지 확인합니다.
	 */
	bool bIsMouseMode_ = true;
};