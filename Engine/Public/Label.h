#pragma once

#include "Color.h"
#include "Vector.hpp"
#include "GameObject.h"


/**
 * @brief 게임 내의 라벨 오브젝트입니다.
 */
class Label : public GameObject
{
public:
	/**
	 * @brief 게임 내의 라벨 생성자입니다.
	 * 
	 * @note 텍스트 문자열은 반드시 아스키 코드 범위 내에 있는 문자들로 구성되어야 합니다.
	 *
	 * @param Signature 게임 라벨의 식별자입니다.
	 * @param Text 게임 라벨의 텍스트입니다.
	 * @param FontSignature 게임 라벨의 문자열의 폰트 시그니처입니다.
	 * @param Position 월드 상의 게임 라벨 위치입니다.
	 * @param Color 텍스트의 색상입니다.
	 */
	Label(
		const std::string& Signature, 
		const std::wstring& Text, 
		const std::string& FontSignature,
		const Vec2f& Position, 
		const LinearColor& Color
	);


	/**
	 * @brief 게임 라벨의 가상 소멸자입니다.
	 */
	virtual ~Label() {}


	/**
	 * @brief 명시적으로 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Label);


	/**
	 * @brief 게임 라벨를 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief 월드 상의 게임 라벨 위치를 설정합니다.
	 *  
	 * @param Position 설정할 게임 라벨의 위치입니다.
	 */
	void SetPosition(const Vec2f& Position) { Position_ = Position; }


	/**
	 * @brief 게임 라벨를 설정합니다.
	 *
	 * @note 텍스트 문자열은 반드시 아스키 코드 범위 내에 있는 문자들로 구성되어야 합니다.
	 *
	 * @param Text 설정할 게임 라벨입니다.
	 */
	void SetText(const std::wstring& Text) { Text_ = Text; }


	/**
	 * @brief 게임 라벨의 색상을 설정합니다.
	 * 
	 * @param Color 설정할 게임 라벨의 색상입니다.
	 */
	void SetColor(const LinearColor& Color) { Color_ = Color; }


private:
	/**
	 * @brief 화면에 표시될 게임 라벨입니다.
	 */
	std::wstring Text_;


	/**
	 * @brief 게임 라벨 문자열의 폰트 시그니처입니다.
	 */
	std::string FontSignature_;


	/**
	 * @brief 월드 상에 표시될 게임 라벨의 중심 위치입니다.
	 */
	Vec2f Position_;


	/**
	 * @brief 월드에 표시될 게임 라벨 색상입니다.
	 */
	LinearColor Color_;
};